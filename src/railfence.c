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


/* Encryption */
CryptoUtil_ErrorCode
Railfence_Encrypt(const char *pt,  // In
                  uint64 ptLen,    // In
                  uint64 key,      // In
                  char *ct,        // Out
                  uint64 ctLen)    // In
{
    if (pt == NULL || ct == NULL \
        || ptLen == 0 || ctLen != ptLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    if (key == 1) {
       memcpy(ct, pt, ptLen);
       return CryptoUtil_Error_Success;
    }
   
    int i=0;
    int rail=0;
    int preRail=-1;
    int rails=key; 
    Move_Direction md=DOWN;
    int base_rails[rails];
    int pos_rails[rails];

    /*
     * Compute start position of each rail's 1st element in ciphertext:
     *   firstly, get the number of elements of each rail; secondly, compute
     *   the start position of each rail based on the number of elements of
     *   each rail.
     *   
     */
    memset(base_rails, 0, sizeof(base_rails));
    for (i=0; i<ptLen; i++) {
        rail = RailfenceGetNextRail(preRail, rails, &md);
        assert(rail>=0 && rail<rails);
        base_rails[rail]++;
        preRail = rail;
    }

    i = rails-1;
    /* printf("DEBUG num_rails[%d]=%d ", i, base_rails[i]); */
    base_rails[i] = ptLen - base_rails[i];
    /* printf("DEBUG base_rails[%d]=%d\n", i, base_rails[i]); */
    i--;
    while (i >= 0) {
        /* printf("DEBUG base_rails[%d]=%d, num_rails[%d]=%d ", i+1,
           base_rails[i+1], i, base_rails[i]); */
        base_rails[i] = base_rails[i+1] - base_rails[i];
        /* printf(" base_rails[%d]=%d\n", i, base_rails[i]); */
        i--;
    }
   
    /*
     * Compute ciphertext of different rails in parallel.
     */
    preRail = -1;
    md = DOWN;
    memset(pos_rails, 0, sizeof(pos_rails)); 
    for (i=0; i<ptLen; i++) {
        rail = RailfenceGetNextRail(preRail, rails, &md);        
        int ctPos = base_rails[rail] + pos_rails[rail];
        ct[ctPos] = pt[i];
        /*printf("DEBUG PT[%d]=%c, rail=%d, base_rail_pos=%d, rail_pos=%d, ctPos=%d\n", i,
               pt[i], rail, base_rails[rail], pos_rails[rail], ctPos);
        */
        pos_rails[rail]++;
        preRail = rail;
    }

    return CryptoUtil_Error_Success;
}
