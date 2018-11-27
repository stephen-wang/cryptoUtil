#ifndef _CRYPTOUTIL_ERRORS_H_
#define _CRYPTOUTIL_ERRORS_H_


typedef enum CryptoUtil_Error_Code CryptoUtil_Error_Code;

#define CryptoUtil_Error_Defs \
   def(CryptoUtil_Error_Success, "Success", 0) \
   def(CryptoUtil_Error_InvalidParam, "Invalid Parameter", 1) \
   def(CryptoUtil_Error_Failure, "Unknown failure", 2)

enum CryptoUtil_Error_Code {
#define def(code, desc, val) code = val,
   CryptoUtil_Error_Defs
#undef def
};


#define def(code, desc, val) desc,
const char *CryptoUtil_Error_Strs[] = { CryptoUtil_Error_Defs };
#define cryptoUtilErrorDesc(code) \
    CryptoUtil_Error_Strs[code - CryptoUtil_Error_Success]
#undef def
      


#endif
