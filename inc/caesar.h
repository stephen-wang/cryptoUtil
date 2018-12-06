/* Copyright (c) 2018, wenzhi wang */

#ifndef _CAESAR_H_
#define _CAESAR_H_

#include "cryptoUtil_errors.h"
#include "cryptoUtil_types.h"


CryptoUtil_ErrorCode Caesar_Encrypt(const char *pt, uint64 ptLen, uint8 key, \
                                    char *ct, uint64 ctLen);
CryptoUtil_ErrorCode Caesar_Decrypt(const char *ct, uint64 ctLen, uint8 key, \
                                    char *pt, uint64 ptLen);

#endif
