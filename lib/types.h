/* types.h
 *
 * Type system for L-Script
 */

#ifndef TYPES_H
#define TYPES_H

#include "config.h"

typedef enum
{
    LS_INVALID_T = 0,
    LS_INT_T = 1,
    LS_FLOAT_T = 2,
    LS_BOOL_T = 4,
    LS_CHAR_T = 8,
    LS_FUNC_T = 16,
    LS_LIST_T = 32,
    LS_SYMBOL_T = 64,
} LSType;

#ifndef __bool_true_false_are_defined
typedef enum {false, true} bool;
#endif

typedef struct LSData
{
    LSType type;
    union
    {
        int ival;
        float fval;
        bool bval;
        char cval;
        char sym[LS_MAX_SYM_LEN + 1];
    };
} LSData;

#define LS_NUMERIC_T (LS_INT_T | LS_FLOAT_T)
#define LS_ATOMIC_T (LS_NUMERIC_T | LS_BOOL_T | LS_CHAR_T | LS_SYMBOL_T)
#define LS_ANY_T (LS_ATOMIC_T | LS_FUNC_T | LS_LIST_T)

#define LS_NULL (LSData) {.type = LS_INVALID_T }
#define LS_IS_NULL(d) ((d).type == LS_INVALID_T)

#endif
