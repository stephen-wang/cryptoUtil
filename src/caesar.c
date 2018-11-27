#include "stdio.h"
#include "caesar.h"
#include "string.h"

/*
 * Encrypt plaintext by right shifting each alphabetic character 'key' bits.
 */
CryptoUtil_Error_Code
CaesarEncrypt(const char *pt, uint64 ptLen, uint8 key, char *ct, uint64 ctLen)
{
    if (pt == NULL || ct == NULL || ptLen <=0 || ptLen != ctLen) {
        return CryptoUtil_Error_InvalidParam;
    }

    for (int i = 0; i < ptLen; i++) { 

        ct[i] = pt[i];

        if (pt[i] >= 'a' && pt[i] <= 'z') {
            ct[i] = 'a' + (pt[i] - 'a' + key) % 26;
        } else if (pt[i] >= 'A' && pt[i] <= 'Z') {
            ct[i] = 'A' + (pt[i] - 'A' + key) % 26;
        }
    }

    return CryptoUtil_Error_Success;
}

int main(void)
{
    char *pt = NULL;
    char *expCt = NULL; 
    int len;
    char buf[256];
    int key;
    CryptoUtil_Error_Code rc;

    /*
     * Case 1: Encrypt text only containing lower alphatetic characters.
     */
    pt = "abcdewxz";
    expCt = "defghzac";
    key = 3; 

    len = strlen(pt);
    rc = CaesarEncrypt(pt, len, key, buf, len);
    if (rc != CryptoUtil_Error_Success) {
        printf("Caesar encryption failed: %d (%s)\n",\
               rc, cryptoUtilErrorDesc(rc));
        goto Error;
    }

    len = strlen(expCt);
    if (strncmp(buf, expCt, len) != 0) {
        printf("Caesar encryption(PT<%s>/key<%d>) failed, expect :<%s>, actual "
               "CT:<%s>\n", pt, key, expCt, buf);
        rc = CryptoUtil_Error_Failure;
        goto Error;
    }

    printf("Case testCaesarEncrypt() passed\n");
    return rc;

Error:
    printf("Case testCaesarEncrypt() failed\n");
    return rc;
 
}
