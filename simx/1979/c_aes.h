#ifndef C_AES_H
#define C_AES_H

#include <stdio.h>

#if !defined(NO_FILE_SYSTEM)
int decryptLine(char** buf, int* bufLen, FILE* fp, size_t* strLen);
#endif

#endif
