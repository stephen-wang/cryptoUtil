/* Copyright (c) 2018, wenzhi wang */

#include <stdio.h>
#include <string.h>

#include "caesar.h"
#include "cryptoUtil_types.h"


typedef struct { char oriCh;
    char expCh;
    int shift;
} ShiftVec;


int
testCaesarShift()
{
    ShiftVec testVectors[5] = { {'a', 'b', 1},
                                {'b', 'd', 2},
                                {'Y', 'B', 3},
                                {'a', 'z', -1},
                                {'a', 'y', -2}};

    for (int i=0; i < sizeof testVectors/sizeof(ShiftVec); i++) {
        ShiftVec vec = testVectors[i];
        char actCh = CaesarShift(vec.oriCh, vec.shift);
        if (actCh != vec.expCh) {
            printf("**Error** CaesarShift(%c, %d), expect %c, actual %c\n", vec.oriCh, vec.shift, vec.expCh, actCh);
             return -1;
        }
    }

    printf("Case testCaesarShift() passed\n");
    return 0;
}


CryptoUtil_Error_Code
CompareStr(const char *actStr, const char *expStr, int len)
{
    if (strncmp(actStr, expStr, len) != 0) {
        printf("Expect: %s, actual: %s\n", expStr, actStr);
        return CryptoUtil_Error_Failure;
    }

    return CryptoUtil_Error_Success;
}


CryptoUtil_Error_Code
testEncryption(const char *pt, int ptLen, int key, const char *expCt)
{
    CryptoUtil_Error_Code rc=0;
    char buf[256];

    //printf("TestEncryption: PT <%s>, Key <%d>\n", pt, key);
    rc = CaesarEncrypt(pt, ptLen, key, buf, ptLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("**Error** Encryption: %d (%s)\n", rc, cryptoUtilErrorDesc(rc));
        return rc;
    }

    buf[ptLen] = '\0';
    rc = CompareStr(buf, expCt, ptLen);

    return rc;
}


CryptoUtil_Error_Code
testDecryption(const char *ct, int ctLen, int key, const char *expPt)
{
    CryptoUtil_Error_Code rc=0;
    char buf[256];

    //printf("TestDecryption: CT <%s>, Key <%d>\n", ct, key);
    rc = CaesarDecrypt(ct, ctLen, key, buf, ctLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("**Error** Decryption: %d (%s)\n", rc, cryptoUtilErrorDesc(rc));
        return rc;
    }

    buf[ctLen] = '\0';
    rc = CompareStr(buf, expPt, ctLen);
    return rc;
}


CryptoUtil_Error_Code
testCaesarCipher()
{
    char *pt = NULL;
    char *ct = NULL;
    char *expCt = NULL; 
    char *expPt = NULL; 
    int len;
    int key;
    CryptoUtil_Error_Code rc;

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

    printf("Case testCaesarCipher() passed\n");
    return rc;

Error:
    printf("Case testCaesarCipher() failed\n");
    return rc;
 
}


int main(void) {
    int result = 0;
    result += testCaesarShift();
    result += testCaesarCipher();

    return result;
}
