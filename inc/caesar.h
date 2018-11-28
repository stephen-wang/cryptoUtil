/* Copyright (c) 2018, wenzhi wang */

#ifndef _CAESAR_H_
#define _CAESAR_H_

#include "cryptoUtil_errors.h"
#include "cryptoUtil_types.h"


char CaesarShift(char ch, int count);
CryptoUtil_Error_Code CaesarEncrypt(const char *pt, uint64 ptLen, uint8 key, \
                                    char *ct, uint64 ctLen);
CryptoUtil_Error_Code CaesarDecrypt(const char *ct, uint64 ctLen, uint8 key, \
                                    char *pt, uint64 ptLen);

#endif
