/* Copyright (c) 2018, wenzhi wang */

/* 
 * The Vigenère cipher is a method of encrypting alphabetic text by using a
 * series of interwoven Caesar ciphers, based on the letters of a keyword.
 *
 * For more introductions, please refer to:
 * https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher
 */

#include <stdio.h>
#include <ctype.h>

#include "vigenere.h"
#include "utils.h"


/* Check and return if the key for Vigenere Cipher is valid */
bool
Vigenere_ValidKey(const char *key, // IN
                  uint8 keyLen)    // IN
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


/* Vigenere encryption */
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


/* Vigenere decryption */
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
