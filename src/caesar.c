/* Copyright (c) 2018, wenzhi wang */

/* The Caesar cipher, also known as Caesar's cipher, the shift cipher, Caesar's
   code or Caesar shift, is one of the simplest and most widely known encryption
   techniques. It is a type of substitution cipher in which each letter in the
   plaintext is replaced by a letter some fixed number of positions down the
   alphabet. 

   For more introductions, refere to https://en.wikipedia.org/wiki/Caesar_cipher
 */


#include "stdio.h"
#include "string.h"

#include "caesar.h"
#include "utils.h"



/*
 * Encrypt plaintext by right shifting each alphabetic character 'key' places.
 */
CryptoUtil_ErrorCode
Caesar_Encrypt(const char *pt, // IN
               uint64 ptLen,   // IN
               uint8 key,      // IN
               char *ct,       // IN
               uint64 ctLen)   // IN
{
    if (pt == NULL || ct == NULL || ptLen <=0 || ptLen != ctLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i = 0; i < ptLen; i++) { 
        ct[i] = ShiftAlpha(pt[i], key);
    }

    return CryptoUtil_Error_Success;
}


/*
 *  Decrypt ciphertext by left shifting each alphabetic character 'key' places.
 */
CryptoUtil_ErrorCode
Caesar_Decrypt(const char *ct, // IN
               uint64 ctLen,   // IN
               uint8 key,      // IN
               char *pt,       // OUT
               uint64 ptLen)   // IN
{
    if (pt == NULL || ct == NULL || ptLen <=0 || ptLen != ctLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i = 0; i < ptLen; i++) { 

        pt[i] = ShiftAlpha(ct[i], -key);
    }

    return CryptoUtil_Error_Success;
}
