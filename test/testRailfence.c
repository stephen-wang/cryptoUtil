/* Copyright (c) 2018, wenzhi wang */

#include <stdio.h>
#include <string.h>

#include "cryptoUtil_types.h"
#include "common.h"
#include "railfence.h"


CryptoUtil_ErrorCode
testEncryption(const char *pt, int ptLen, int key, const char *expCt)
{
    CryptoUtil_ErrorCode rc=0;
    char buf[256];

    rc = Railfence_Encrypt(pt, ptLen, key, buf, ptLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("  **Error** Encryption: PT <%s>, Key <%d>, %d (%s)\n", pt, key,
               rc, CryptoUtil_ErrorDesc(rc));
        return rc;
    }

    buf[ptLen] = '\0';
    rc = CompareStr(buf, expCt, ptLen);

    return rc;
}


int
testRailfenceCipher()
{
    char *pt = NULL;
    char *expCt = NULL; 
    int len;
    int key;
    int rc=0;

    printf("Case testRaifenceCipher started\n");

    /* case 1 */
    pt = "meetmelater";
    len = strlen(pt);
    expCt = "mmteteaeelr";
    key = 3; 
    if ((rc=testEncryption(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       rc = 1;
       goto Error;   
    }

    printf("Case testRaifenceCipher passed\n\n");

Error:
    printf("Case testRailfenceCipher() failed\n\n");
    return rc;
}


int main(void)
{
    int result = 0;
    result += testRailfenceCipher();

    return result;
}
