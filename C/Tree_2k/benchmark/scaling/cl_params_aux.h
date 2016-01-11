#ifndef CL_TYPECHECK_HDR
#define CL_TYPECHECK_HDR

#define EXIT_CL_ALLOC_FAIL 2
#define EXIT_CL_MISSING_VALUE 3
#define EXIT_CL_INVALID_VALUE 4
#define EXIT_CL_FILE_OPEN_FAIL 5
#define EXIT_CL_INVALID_STRING 6

int isIntCL(char *input, int isVerbose);
int isLongCL(char *input, int isVerbose);
int isFloatCL(char *input, int isVerbose);
int isDoubleCL(char *input, int isVerbose);
void shiftCL(int *i, int argc, char *argv[]);
int isCommentCL(char *str);
int isEmptyLineCL(char *str);
void stripQuotesCL(char *str);

#endif

