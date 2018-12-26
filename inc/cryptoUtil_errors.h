#ifndef _CRYPTOUTIL_ERRORS_H_
#define _CRYPTOUTIL_ERRORS_H_

typedef enum CryptoUtil_ErrorCode CryptoUtil_ErrorCode;

#define CryptoUtil_Error_Defs                                  \
   def(CryptoUtil_Error_Success, "Success", 0) ,               \
   def(CryptoUtil_Error_InvalidParam, "Invalid Parameter", 1), \
   def(CryptoUtil_Error_OutOfMem, "Out of Memory", 2),         \
   def(CryptoUtil_Error_Failure, "Unknown failure", 3)

enum CryptoUtil_ErrorCode {
#define def(code, desc, val) code = val
   CryptoUtil_Error_Defs
#undef def
};

#define def(code, desc, val) desc
#define Err_Strs ((char *[]) {CryptoUtil_Error_Defs})

#define CryptoUtil_ErrorDesc(errCode) \
    Err_Strs[errCode - CryptoUtil_Error_Success]

#endif
