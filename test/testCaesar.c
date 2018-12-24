/* Copyright (c) 2018, wenzhi wang */

#include <stdio.h>
#include <string.h>

#include "caesar.h"
#include "cryptoUtil_types.h"


CryptoUtil_ErrorCode
CompareStr(const char *actStr, const char *expStr, int len)
{
    if (strncmp(actStr, expStr, len) != 0) {
        printf("Expect: %s, actual: %s\n", expStr, actStr);
        return CryptoUtil_Error_Failure;
    }

    return CryptoUtil_Error_Success;
}


CryptoUtil_ErrorCode
testEncryption(const char *pt, int ptLen, int key, const char *expCt)
{
    CryptoUtil_ErrorCode rc=0;
    char buf[256];

    rc = Caesar_Encrypt(pt, ptLen, key, buf, ptLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("  **Error** PT <%s>, key <%d>, Encryption: %d (%s)\n", pt, key,
               rc, CryptoUtil_ErrorDesc(rc));
        return rc;
    }

    buf[ptLen] = '\0';
    rc = CompareStr(buf, expCt, ptLen);

    return rc;
}


CryptoUtil_ErrorCode
testDecryption(const char *ct, int ctLen, int key, const char *expPt)
{
    CryptoUtil_ErrorCode rc=0;
    char buf[256];

    rc = Caesar_Decrypt(ct, ctLen, key, buf, ctLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("  **Error** Decryption: CT <%s>, Key <%d>, %d (%s)\n", ct, key,
               rc, CryptoUtil_ErrorDesc(rc));
        return rc;
    }

    buf[ctLen] = '\0';
    rc = CompareStr(buf, expPt, ctLen);
    return rc;
}


CryptoUtil_ErrorCode
testCaesarCipher()
{
    char *pt = NULL;
    char *ct = NULL;
    char *expCt = NULL; 
    char *expPt = NULL; 
    int len;
    int key;
    CryptoUtil_ErrorCode rc;

    printf("Case testCaesarCipher() started\n");
    /*
     * Case 1: Encrypt/Decrypt text only containing lower alphatetic characters.
     */
    pt = "abcdewxz";
    len = strlen(pt);
    expCt = "defghzac";
    key = 3; 

    if (testEncryption(pt, len, key, expCt) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    ct = expCt;
    expPt = pt;
    if (testDecryption(ct, len, key, expPt) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    /*
     * Case 2: Encrypt text only containing upper alphatetic characters.
     */
    pt = "ABCXYZ";
    len = strlen(ct);
    expCt= "EFGBCD";
    key = 4; 

    if ((rc=testEncryption(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    ct = expCt;
    expPt = pt;
    if ((rc=testDecryption(ct, len, key, expPt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    /*
     * Case 3: Encrypt/Decrypt text containing both digits and alphatbeic characters.
     */
    pt = "78ABCXYZ01";
    len = strlen(pt);
    expCt = "78EFGBCD01";
    key = 4; 

    if ((rc=testEncryption(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    ct = expCt;
    expPt = pt;
    if ((rc=testDecryption(ct, len, key, expPt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    printf("Case testCaesarCipher() passed\n\n");
    return rc;

Error:
    printf("Case testCaesarCipher() failed\n\n");
    return rc;
 
}


int main(void)
{
    int result = 0;
    result += testCaesarCipher();

    return result;
}
