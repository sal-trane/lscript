/*
 * errors.c
 */

#include "errors.h"

enum LSError LSERR = NOERR;

const char* ls_err_desc()
{
    switch (LSERR)
    {
        case NOERR:
            return "NOERR";
        case EHEAPOVERFLOW:
            return "EHEAPOVERFLOW";
        case ESTACKOVERFLOW:
            return "ESTACKOVERFLOW";
        case ESTACKEMPTY:
            return "ESTACKEMPTY"; 
        case EWRONGTYPE: 
            return "EWRONGTYPE";
        case ENOTFOUND:
            return "ENOTFOUND";
        case EDIVZERO:
            return "EDIVZERO";
        case EUNEXPECTEDTOKEN:
            return "EUNEXPECTEDTOKEN";
        case EUNEXPECTEDEOF:
            return "EUNEXPECTEDEOF";
        case ELISTEMPTY:
            return "ELISTEMPTY";
    }
    return "";
}
