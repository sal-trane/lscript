/*
 * util.c
 * Utility functions for L-Script core
 */

#include "util.h"
#include "config.h"

const char* sym_copy(const char* sym, char* buffer)
{
    int i, j;
    for(i = 0; i < LS_MAX_SYM_LEN; i++)
    {
        for(j = 0; LS_ALLOWED_SYMBOL_CHARS[j] != '\0'; j++)
        {
            if (sym[0] == LS_ALLOWED_SYMBOL_CHARS[j])
            {
                buffer[i] = sym[0];
                sym++;
                break;
            }
            else
            {
                buffer[i] = '\0';
            }
        }
    }
    buffer[i] = '\0';
    return sym;
}

bool sym_cmp(const char* sym, const char* toCmp)
{
    int i, j;
    for(i = 0; i < LS_MAX_SYM_LEN; i++)
    {
        if (sym[i] != toCmp[i])
        {
            return false;
        }
        else if (sym[i] == '\0' || toCmp[i] == '\0')
        {
            break;
        }
    }
    if (sym[i] == '\0')
    {
        for(j = 0; LS_ALLOWED_SYMBOL_CHARS[j] != '\0'; j++)
        {
            if (toCmp[i] == LS_ALLOWED_SYMBOL_CHARS[j])
            {
                return false;
            }
        }
    }
    else if (toCmp[i] == '\0')
    {
        for(j = 0; LS_ALLOWED_SYMBOL_CHARS[j] != '\0'; j++)
        {
            if (sym[i] == LS_ALLOWED_SYMBOL_CHARS[j])
            {
                return false;
            }
        }
    }

    return true;
}
