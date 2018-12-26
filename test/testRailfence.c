/* Copyright (c) 2018, wenzhi wang */

#include <stdio.h>
#include <string.h>

#include "cryptoUtil_types.h"
#include "common.h"
#include "railfence.h"


static CryptoUtil_ErrorCode
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


static CryptoUtil_ErrorCode
testDecryption(const char *ct, int ctLen, int key, const char *expPt)
{
    CryptoUtil_ErrorCode rc=0;
    char buf[256];

    rc = Railfence_Decrypt(ct, ctLen, key, buf, ctLen);
    if (rc != CryptoUtil_Error_Success) {
        goto ErrorOut;
    }

    buf[ctLen] = '\0';
    rc = CompareStr(buf, expPt, ctLen);
    if (rc != CryptoUtil_Error_Success) {
        goto ErrorOut;
    }
    return rc;

ErrorOut:
    printf("  **Error** Decryption: CT <%s>, Key <%d>, %d (%s)\n", ct, key,
            rc, CryptoUtil_ErrorDesc(rc));
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
    expCt = "meetmelater";
    key = 1; 
    if ((rc=testEncryption(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       rc = 1;
       goto Error;   
    }

    if ((rc=testDecryption(expCt, len, key, pt)) != CryptoUtil_Error_Success) {
       rc = 1;
       goto Error;   
    }


    /* case 2 */
    pt = "meetmelater";
    len = strlen(pt);
    expCt = "memltreteae";
    key = 2; 
    if ((rc=testEncryption(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       rc = 1;
       goto Error;   
    }

    if ((rc=testDecryption(expCt, len, key, pt)) != CryptoUtil_Error_Success) {
       rc = 1;
       goto Error;   
    }

    /* case 3 */
    pt = "meetmelater";
    len = strlen(pt);
    expCt = "mmteteaeelr";
    key = 3; 
    if ((rc=testEncryption(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       rc = 1;
       goto Error;   
    }

    if ((rc=testDecryption(expCt, len, key, pt)) != CryptoUtil_Error_Success) {
       rc = 1;
       goto Error;   
    }

    printf("Case testRaifenceCipher passed\n\n");
    return rc;

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
