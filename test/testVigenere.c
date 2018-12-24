/* Copyright (c) 2018, wenzhi wang */

#include <stdio.h>
#include <string.h>

#include "vigenere.h"
#include "cryptoUtil_types.h"


CryptoUtil_ErrorCode
CompareStr(const char *actStr, const char *expStr, int len)
{
    if (strncmp(actStr, expStr, len) != 0) {
        printf("  Expect: %s, actual: %s\n", expStr, actStr);
        return CryptoUtil_Error_Failure;
    }

    return CryptoUtil_Error_Success;
}


CryptoUtil_ErrorCode
testEncryption(const char *pt, int ptLen, char *key, const char *expCt)
{
    CryptoUtil_ErrorCode rc=0;
    char buf[256];

    rc = Vigenere_Encrypt(pt, ptLen, key, strlen(key), buf, ptLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("  **Error** Encryption: PT <%s>, Key <%s>, %d (%s)\n", pt, key,
               rc, CryptoUtil_ErrorDesc(rc));
        return rc;
    }

    buf[ptLen] = '\0';
    rc = CompareStr(buf, expCt, ptLen);

    return rc;
}


CryptoUtil_ErrorCode
testDecryption(const char *ct, int ctLen, char *key, const char *expPt)
{
    CryptoUtil_ErrorCode rc=0;
    char buf[256];

    rc = Vigenere_Decrypt(ct, ctLen, key, strlen(key), buf, ctLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("  **Error** Decryption: CT <%s>, key <%s>, %d (%s)\n", ct, key,
               rc, CryptoUtil_ErrorDesc(rc));
        return rc;
    }

    buf[ctLen] = '\0';
    rc = CompareStr(buf, expPt, ctLen);
    return rc;
}


CryptoUtil_ErrorCode
testVigenereCipher()
{
    char *pt = NULL;
    char *ct = NULL;
    char *expCt = NULL; 
    char *expPt = NULL; 
    char *key = NULL;
    int len;
    CryptoUtil_ErrorCode rc;

    printf("Case testVigenereCipher started\n");
    /*
     * Case 1: Encrypt/Decrypt text only containing lower alphatetic characters.
     */
    pt = "abcd";
    len = strlen(pt);
    expCt = "bcee";
    key = "aab";

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
    pt = "abc12";
    len = strlen(ct);
    expCt= "ceg12";
    key = "bcdee";

    if ((rc=testEncryption(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    ct = expCt;
    expPt = pt;
    if ((rc=testDecryption(ct, len, key, expPt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    printf("Case testVigenereCipher passed\n\n");
    return rc;

Error:
    printf("Case testVigenereCipher() failed\n\n");
    return rc;
 
}


int main(void)
{
    int result = 0;
    result += testVigenereCipher();

    return result;
}
