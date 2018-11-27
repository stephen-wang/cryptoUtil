#include <stdio.h>
#include <string.h>

#include "cryptoUtil_types.h"
#include "caesar.h"


CryptoUtil_Error_Code
run(const char *pt, int ptLen, int key, const char *expCt)
{
    CryptoUtil_Error_Code rc;
    char buf[256];

    rc = CaesarEncrypt(pt, ptLen, key, buf, ptLen);
    if (rc != CryptoUtil_Error_Success) {
        printf("**Error** Encryption: %d (%s)\n", rc, cryptoUtilErrorDesc(rc));
        return rc;
    }

    buf[ptLen] = '\0';
    if (strncmp(buf, expCt, ptLen) != 0) {
        printf("**Error** Encrypt PT<%s>/key<%d>, expect<%s>, actual<%s>\n",
               pt, key, expCt, buf);
        return CryptoUtil_Error_Failure;
    }

    return CryptoUtil_Error_Success;
}

CryptoUtil_Error_Code
testCaesarEncrypt()
{
    char *pt = NULL;
    char *expCt = NULL; 
    int len;
    int key;
    CryptoUtil_Error_Code rc;

    /*
     * Case 1: Encrypt text only containing lower alphatetic characters.
     */
    pt = "abcdewxz";
    len = strlen(pt);
    expCt = "defghzac";
    key = 3; 

    if (run(pt, len, key, expCt) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    /*
     * Case 2: Encrypt text only containing upper alphatetic characters.
     */
    pt = "ABCXYZ";
    len = strlen(pt);
    expCt = "EFGBCD";
    key = 4; 

    if ((rc=run(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    /*
     * Case 3: Encrypt text containing both digits and alphatbeic characters.
     */
    pt = "78ABCXYZ01";
    len = strlen(pt);
    expCt = "78EFGBCD01";
    key = 4; 

    if ((rc=run(pt, len, key, expCt)) != CryptoUtil_Error_Success) {
       goto Error;   
    }

    printf("Case testCaesarEncrypt() passed\n");
    return rc;

Error:
    printf("Case testCaesarEncrypt() failed\n");
    return rc;
 
}

int main(void) {
    testCaesarEncrypt();
}
