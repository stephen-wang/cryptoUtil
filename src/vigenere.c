/* Copyright (c) 2018, wenzhi wang */

/* standard libs */
#include <stdio.h>
#include <ctype.h>

/* cryptoUtil headers */
#include "vigenere.h"
#include "utils.h"


bool
Vigenere_ValidKey(const char *key,
                  uint8 keyLen)
{
    if (key == NULL || keyLen == 0) {
        return false;
    }

    int i=0;
    while (i < keyLen) {
        if (!isalpha(key[i++])) {
            return false;
        }
    }

    return true; 
}


CryptoUtil_ErrorCode
Vigenere_Encrypt(const char *pt,  // In
                 uint64 ptLen,    // In
                 const char *key, // In
                 uint8 keyLen,    // In
                 char *ct,        // Out
                 uint64 ctLen)    // In
{
    if (pt == NULL || ct == NULL \
        || ptLen == 0 || ctLen != ptLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    if (!Vigenere_ValidKey(key, keyLen)) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i=0; i < ptLen; i++) {
       if (isalpha(pt[i])) {
           int pos = i % keyLen;
           ct[i] = ShiftAlpha(pt[i], tolower(key[pos])-'a'+1);
       } else {
           ct[i] = pt[i];
       }
    }

    return CryptoUtil_Error_Success;
}

                                    
CryptoUtil_ErrorCode
Vigenere_Decrypt(const char *ct,   // In
                 uint64 ctLen,     // In
                 const char *key,  // In
                 uint8 keyLen,     // In
                 char *pt,         // Out
                 uint64 ptLen)     // In
{
    if (pt == NULL || ct == NULL \
        || ptLen == 0 || ctLen != ptLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    if (! Vigenere_ValidKey(key, keyLen)) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i=0; i < ptLen; i++) {
       if (isalpha(ct[i])) {
           int pos = i % keyLen;
           pt[i] = ShiftAlpha(ct[i], -(tolower(key[pos])-'a'+1));
       } else {
           pt[i] = ct[i];
       }
    }

    return CryptoUtil_Error_Success;
}
