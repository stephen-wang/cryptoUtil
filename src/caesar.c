/* Copyright (c) 2018, wenzhi wang */

/* standard libs */
#include "stdio.h"
#include "string.h"

/* cryptoUtil headers */
#include "caesar.h"
#include "utils.h"


/*
 * Encrypt plaintext by right shifting each English character 'key' positions.
 */

CryptoUtil_ErrorCode
Caesar_Encrypt(const char *pt, uint64 ptLen, uint8 key, char *ct, uint64 ctLen)
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
 *  Decrypt ciphertext by left shifting each English character 'key' positions.
 */

CryptoUtil_ErrorCode
Caesar_Decrypt(const char *ct, uint64 ctLen, uint8 key, char *pt, uint64 ptLen)
{
    if (pt == NULL || ct == NULL || ptLen <=0 || ptLen != ctLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i = 0; i < ptLen; i++) { 

        pt[i] = ShiftAlpha(ct[i], -key);
    }

    return CryptoUtil_Error_Success;
}
