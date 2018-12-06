/* Copyright (c) 2018, wenzhi wang */

#ifndef _VIGENERE_H_
#define _VIGENERE_H_

#include "cryptoUtil_errors.h"
#include "cryptoUtil_types.h"


CryptoUtil_ErrorCode Vigenere_Encrypt(const char *pt, uint64 ptLen,
                                       const char *key, uint8 keyLen,
                                       char *ct, uint64 ctLen);
CryptoUtil_ErrorCode Vigenere_Decrypt(const char *ct, uint64 ctLen,
                                       const char *key, uint8 keyLen, 
                                       char *pt, uint64 ptLen);

#endif
