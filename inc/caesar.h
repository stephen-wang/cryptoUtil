#ifndef _CAESAR_H_
#define _CAESAR_H_

#include "cryptoUtil_errors.h"
#include "cryptoUtil_types.h"

CryptoUtil_Error_Code CaesarEncrypt(const char *pt, uint64 ptLen, uint8 key, \
                                    char *ct, uint64 ctLen);

#endif
