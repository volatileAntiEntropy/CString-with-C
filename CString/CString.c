#include "CString.h"

bool InitializeCString(CString *structCString, size_t __autoExpandLength)
{
    if (structCString != NULL && structCString->pstr != NULL)
    {
        structCString->autoExpandLength = __autoExpandLength;
        structCString->pstr = (char *)malloc(structCString->autoExpandLength * sizeof(char));
        structCString->pstr[0] = '\0';
        structCString->length = 0;
        structCString->capacity = structCString->autoExpandLength;
        return true;
    }
    else
    {
        return false;
    }
}

bool ReserveWithoutRelease(CString *structCString, size_t newCapacity)
{
    if (structCString != NULL && structCString->pstr != NULL && newCapacity > structCString->capacity)
    {
        char *temp = (char *)malloc(newCapacity * sizeof(char));
        memcpy(temp, structCString->pstr, structCString->capacity * sizeof(char));
        structCString->pstr = temp;
        structCString->capacity = newCapacity;
        return true;
    }
    else
    {
        return false;
    }
}

bool ConcatChar(CString *structCString, char c)
{
    if (structCString != NULL && structCString->pstr != NULL)
    {
        if (structCString->capacity - structCString->length > 1)
        {
            structCString->pstr[structCString->length] = c;
            structCString->pstr[structCString->length + 1] = '\0';
            structCString->length++;
        }
        else
        {
            size_t newCapacity = structCString->capacity + structCString->autoExpandLength;
            ReservWithoutRelease(structCString, newCapacity);
            structCString->pstr[structCString->length] = c;
            structCString->pstr[structCString->length + 1] = '\0';
            structCString->length++;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool ConcatCharArray(CString *structCString, const char *cstr, size_t offset, size_t length)
{
    if (structCString != NULL && structCString->pstr != NULL && offset <= strlen(cstr) && length <= strlen(cstr) - offset + 1)
    {
        if (structCString->length + length >= structCString->capacity)
        {
            ReservWithoutRelease(structCString, structCString->capacity + length);
        }
        memcpy(structCString->pstr + structCString->length, cstr + offset, length);
        structCString->length += length;
        return true;
    }
    else
    {
        return false;
    }
}

bool ConcatCString(CString *structCString, CString *CStringToAdd, size_t offset, size_t length)
{
    if (structCString != NULL && structCString->pstr != NULL && CStringToAdd != NULL && CStringToAdd != NULL)
    {
        return ConcatCharArray(structCString, CStringToAdd->pstr, offset, length);
    }
    else
    {
        return false;
    }
}

bool GetSubstring(CString *structCString, size_t startIndex, size_t length, CString *dest)
{
    if (structCString != NULL && structCString->pstr != NULL && startIndex <= structCString->length && length <= structCString->length - startIndex + 1)
    {
        free(dest);
        dest = (CString *)malloc(sizeof(CString));
        InitializeCString(dest, structCString->autoExpandLength);
        return ConcatCString(dest, structCString, startIndex, length);
    }
    else
    {
        return false;
    }
}