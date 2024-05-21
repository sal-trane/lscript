/*
 * errors.h
 *
 * L-Script error definitions
 */

#ifndef ERRORS_H
#define ERRORS_H

#include "types.h"

/*
 * Definition of differnt errors.
 */
enum LSError
{
    NOERR,              //No error
    EHEAPOVERFLOW,      //Heap overflow
    ESTACKOVERFLOW,     //Stack overflow
    ESTACKEMPTY,        //Stack empty
    EWRONGTYPE,         //Expected a differnt type
    ENOTFOUND,          //Symbol not found
    EDIVZERO,           //Attempt to divide by zero
    EUNEXPECTEDTOKEN,   //Unexpected token during parse
    EUNEXPECTEDEOF,     //Unecpected end of input during parse
    ELISTEMPTY,         //List is empty
};

/*
 * Global error register.
 */
extern enum LSError LSERR;

/*
 * Returns a string representation of the error code.
 */
const char* ls_err_desc();

#endif
