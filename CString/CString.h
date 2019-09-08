#pragma once

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <stdbool.h>

typedef struct
{
    char *pstr;
    size_t length;
    size_t capacity;
    size_t autoExpandLength;
} CString;

bool InitializeCString(CString *structCString, size_t __autoExpandLength);
bool ReserveWithoutRelease(CString *structCString, size_t newCapacity);
bool ConcatChar(CString *structCString, char c);
bool ConcatCharArray(CString *structCString, const char *cstr, size_t offset, size_t length);
bool ConcatCString(CString *structCString, CString *CStringToAdd, size_t offset, size_t length);
bool GetSubstring(CString *structCString, size_t startIndex, size_t length, CString *dest);