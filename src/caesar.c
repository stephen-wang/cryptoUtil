/* Copyright (c) 2018, wenzhi wang */

#include "stdio.h"
#include "string.h"
#include "caesar.h"


/*
 *  Shift English character 'ch' by 'count' positions and return the new
 *  character, e.g.
 *      ch='a', count=1, return 'b'
 *      ch='b', count=2, return 'd'
 *      ch='Y', count=3, return 'B'
 *      ch='a', count=-1, return 'z'
 *      ch='a', count=-2, return 'y'
 */

char
CaesarShift(char ch, int shift)
{
    char result = ch;
    char base = 0;
    //int count = shift;

    if (ch >= 'a' && ch <= 'z') {
        base = 'a';
    } else if (ch >= 'A' && ch <= 'Z') {
        base = 'A';
    }

    if (base != 0) {
       if (shift < 0) {  //left shift
           shift *= -1;
           while (shift > 0) {
               result--;    
               shift--;
               if (result < base) {
                  result = base + 25;
               }
           }
       } else {          // right shift
           while (shift > 0) {
               result++;    
               shift--;
               if (result > base + 25) {
                  result = base;
               }
           }
       }
    }

    //printf("***DEBUG*** %c shift %d --> %c\n", ch, count, result);

    return result;
}


/*
 * Encrypt plaintext by right shifting each English character 'key' positions.
 */

CryptoUtil_Error_Code
CaesarEncrypt(const char *pt, uint64 ptLen, uint8 key, char *ct, uint64 ctLen)
{
    if (pt == NULL || ct == NULL || ptLen <=0 || ptLen != ctLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i = 0; i < ptLen; i++) { 
        ct[i] = CaesarShift(pt[i], key);
    }

    return CryptoUtil_Error_Success;
}


/*
 *  Decrypt ciphertext by left shifting each English character 'key' positions.
 */

CryptoUtil_Error_Code
CaesarDecrypt(const char *ct, uint64 ctLen, uint8 key, char *pt, uint64 ptLen)
{
    if (pt == NULL || ct == NULL || ptLen <=0 || ptLen != ctLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i = 0; i < ptLen; i++) { 

        pt[i] = CaesarShift(ct[i], -key);
    }

    return CryptoUtil_Error_Success;
}
