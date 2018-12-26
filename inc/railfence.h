/* Copyright (c) 2018, wenzhi wang */

#ifndef _RAILFENCE_H_
#define _RAILFENCE_H_ 

#include "cryptoUtil_errors.h"
#include "cryptoUtil_types.h"


CryptoUtil_ErrorCode Railfence_Encrypt(const char *pt, uint64 ptLen, uint64 key,
                                       char *ct, uint64 ctLen);

CryptoUtil_ErrorCode Railfence_Decrypt(const char *ct, uint64 ctLen,  uint64 key,
                                       char *pt,  uint64 ptLen);

#endif
