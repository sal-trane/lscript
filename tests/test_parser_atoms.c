/*
 * Tests the parsing of atoms (numbers, chars, bools)
 */

#include <parser.h>
#include <progheap.h>
#include <errors.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define COMPARE_FLOAT(a, b) (((a) - (b)) < 0.001 && ((a) - (b)) > -0.001)

int main()
{
    LSData* r;

    // Test numeric parsing
    assert(parse_lscript("152"));
    r = get_node(0);
    assert(r->type == LS_INT_T);
    assert(r->ival == 152);
    
    assert(parse_lscript("  -6"));
    r = get_node(0);
    assert(r->type == LS_INT_T);
    assert(r->ival == -6);
    
    assert(parse_lscript("+3.14"));
    r = get_node(0);
    assert(r->type == LS_FLOAT_T);
    assert(COMPARE_FLOAT(r->fval, 3.14));

    assert(!parse_lscript("-..3"));
    assert(LSERR == EUNEXPECTEDTOKEN);

    // Test single char parsing
    assert(parse_lscript("'c'"));
    r = get_node(0);
    assert(r->type == LS_CHAR_T);
    assert(r->cval == 'c');

    assert(parse_lscript("')'"));
    r = get_node(0);
    assert(r->type == LS_CHAR_T);
    assert(r->cval == ')');

    // Test bool parsing
    assert(parse_lscript("#t"));
    r = get_node(0);
    assert(r->type == LS_BOOL_T);
    assert(r->bval == true);

    assert(parse_lscript("#f"));
    r = get_node(0);
    assert(r->type == LS_BOOL_T);
    assert(r->bval == false);

    assert(!parse_lscript("#a"));
    assert(LSERR == EUNEXPECTEDTOKEN);

    // Test symbol parsing
    assert(parse_lscript("foo"));
    r = get_node(0);
    assert(r->type == LS_SYMBOL_T);
    assert(strcmp(r->sym, "foo") == 0);

    assert(parse_lscript("foo[4]"));
    r = get_node(0);
    assert(r->type == LS_SYMBOL_T);
    assert(strcmp(r->sym, "foo[4]") == 0);

    assert(parse_lscript("*"));
    r = get_node(0);
    assert(r->type == LS_SYMBOL_T);
    assert(strcmp(r->sym, "*") == 0);
    
    return 0;
}
