/* Copyright (c) 2018, wenzhi wang */

/* 
 * In the railfence cipher (A.K.A. zigzag cipher), the plain text is written 
 * downwards and diagnoally on successive "rails" on an imaginary fence, then
 * moving up when the bottom rail is reached. When the top rail is rached, the
 * message is written downwards again until the whole plaintext is written out.
 * Then message is read off in rows as ciphertext.
 *
 * Refer to: https://en.wikipedia.org/wiki/Rail_fence_cipher
 */

#include <assert.h>
#include <stdio.h>   // for printf
#include <stdlib.h>
#include <string.h>

#include "railfence.h"
#include "utils.h"


typedef enum {
   UP=0,
   DOWN,
} Move_Direction;


/* Get the rail of plaintext data */
static int
RailfenceGetNextRail(int preRail,        // IN
                     int rails,          // IN
                     Move_Direction *md) // IN/OUT
{
    int rail = preRail;
    //printf("DEBUG RailfenceGetNextRail: preRail %d, rails %d, md:%s ",
    //       preRail, rails, (*md==DOWN ? "DOWN" : "UP")); 
    if (*md == DOWN) {
        rail++;
        if (rail == rails) {
            rail = rails-2;
            *md = UP;
        }
    } else {
        rail--;
        if (rail == -1) {
            rail = 1;
            *md = DOWN;
        }
    }

    return rail;
}


/* Given length of plain/cipher text 'inputLen' and number of rails 'rails',
   get the number of data in each rail. */
static CryptoUtil_ErrorCode
RailfenceGetNumberOfRails(uint64 inputLen,    // IN
                          uint64 *numOfRails, // OUT
                          uint64 rails)       // IN
{
    if (numOfRails == NULL || rails > inputLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    int rail;
    int preRail=-1;
    Move_Direction md=DOWN;

    memset(numOfRails, 0, rails * sizeof(uint64));
    for (uint64 i=0; i<inputLen; i++) {
        rail = RailfenceGetNextRail(preRail, rails, &md);
        assert(rail>=0 && rail<rails);
        numOfRails[rail]++;
        preRail = rail;
    }

    return CryptoUtil_Error_Success;
}


/* Given the length of plain/cipher text 'inputLen' and number of data in each
   rail 'numOfRails', get the position of the first data of each rail in
   ciphertext.

   Note: numOfRails and railsBasePos may share same memory address.
*/
static CryptoUtil_ErrorCode
RailfenceGetRailBasePosInCt(uint64 inputLen,          // IN
                            const uint64 *numOfRails, // IN
                            uint64 rails,             // IN
                            uint64 *railBasePos)      // OUT
{
    if (numOfRails == NULL || railBasePos == NULL || rails > inputLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    int i = rails-1;
    railBasePos[i] = inputLen - numOfRails[i];
    while (--i >= 0) {
        railBasePos[i] = railBasePos[i+1] - numOfRails[i];
    }
   
    return CryptoUtil_Error_Success; 
}


/* Encryption */
CryptoUtil_ErrorCode
Railfence_Encrypt(const char *pt,  // In
                  uint64 ptLen,    // In
                  uint64 key,      // In
                  char *ct,        // Out
                  uint64 ctLen)    // In
{
    if (pt == NULL || ct == NULL \
        || ptLen == 0 || ctLen != ptLen || key >= ptLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    if (key == 1) {
       memcpy(ct, pt, ptLen);
       return CryptoUtil_Error_Success;
    }
   
    int i=0;
    int rail=0;
    int preRail=-1;
    uint64 rails=key; 
    Move_Direction md=DOWN;
    uint64 *baseOfRails;
    uint64 *posOfRails;
    CryptoUtil_ErrorCode rc;

    /*
     * Compute the number of data in each rail.
     */
    baseOfRails = malloc(rails * sizeof(uint64)); 
    if (baseOfRails == NULL) {
        return CryptoUtil_Error_OutOfMem;
    }

    rc = RailfenceGetNumberOfRails(ptLen, baseOfRails, key);
    assert(rc == CryptoUtil_Error_Success);

    /*
     * Compute position of each rail's 1st data in ciphertext.
     */
    rc = RailfenceGetRailBasePosInCt(ptLen, baseOfRails, key, baseOfRails);
    assert(rc == CryptoUtil_Error_Success);
   
    /*
     * Compute ciphertext of different rails in parallel.
     */
    preRail = -1;
    md = DOWN;

    posOfRails = malloc(sizeof(uint64) * rails);
    if (posOfRails == NULL) { 
        return CryptoUtil_Error_OutOfMem;
    }
    memset(posOfRails, 0, sizeof(uint64) * key);

    for (i=0; i<ptLen; i++) {
        rail = RailfenceGetNextRail(preRail, rails, &md);        
        int ctPos = baseOfRails[rail] + posOfRails[rail];
        ct[ctPos] = pt[i];
        posOfRails[rail]++;
        preRail = rail;
    }

    free(posOfRails);
    free(baseOfRails);

    return CryptoUtil_Error_Success;
}


/* Decryption */
CryptoUtil_ErrorCode
Railfence_Decrypt(const char *ct,  // In
                  uint64 ctLen,    // In
                  uint64 key,      // In
                  char *pt,        // Out
                  uint64 ptLen)    // In
{
    if (pt == NULL || ct == NULL \
        || ptLen == 0 || ctLen != ptLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    if (key == 1) {
       memcpy(pt, ct, ctLen);
       return CryptoUtil_Error_Success;
    }


    /*
     * Compute the number of elements for each rail.
     */
    CryptoUtil_ErrorCode rc;
    uint64 *baseOfRails;

    baseOfRails = malloc(key * sizeof(uint64));
    if (baseOfRails == NULL) {
        return CryptoUtil_Error_OutOfMem;
    }

    rc = RailfenceGetNumberOfRails(ptLen, baseOfRails, key);
    assert(rc == CryptoUtil_Error_Success);

    /*
     * Compute position of each rail's 1st data in ciphertext.
     */
    rc = RailfenceGetRailBasePosInCt(ptLen, baseOfRails, key, baseOfRails);
    assert(rc == CryptoUtil_Error_Success);


    /*
     * Decrypt the ciphertext.
     */
    uint64 ptPos = 0;
    uint64 rails = key;
    int rail;
    int preRail = -1;
    uint64 *posOfRails;
    Move_Direction md=DOWN;
    uint64 ctPos;

    posOfRails = malloc(sizeof(uint64) * rails);
    if (posOfRails == NULL) { 
        return CryptoUtil_Error_OutOfMem;
    }

    memset(posOfRails, 0, sizeof(uint64) * rails);
    while(ptPos < ptLen) {
        rail = RailfenceGetNextRail(preRail, rails, &md);
        assert(rail < rails);
        preRail = rail;

        ctPos = baseOfRails[rail] + posOfRails[rail];
        assert(ctPos < ctLen);

        pt[ptPos++] = ct[ctPos];
        posOfRails[rail]++;
    }

    free(posOfRails);
    free(baseOfRails);

    return CryptoUtil_Error_Success;
}
