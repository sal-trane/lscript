/*
 * util.h
 * Utility functions for L-Script core
 */

#ifndef UTIL_H
#define UTIL_H

#include "types.h"

const char* sym_copy(const char* sym, char* buffer);
bool sym_cmp(const char* sym, const char* toCmp);

#endif
