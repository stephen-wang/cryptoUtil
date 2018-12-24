/* Copyright (c) 2018, wenzhi wang */

#include <stdio.h>
#include <string.h>
#include "cryptoUtil_types.h"
#include "common.h"


CryptoUtil_ErrorCode
CompareStr(const char *actStr, const char *expStr, int len)
{
    if (strncmp(actStr, expStr, len) != 0) {
        printf("Expect: %s, actual: %s\n", expStr, actStr);
        return CryptoUtil_Error_Failure;
    }

    return CryptoUtil_Error_Success;
}
