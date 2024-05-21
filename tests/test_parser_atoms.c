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
    assert(parse_lizscript("152"));
    r = get_node(0);
    assert(r->type == LS_INT_T);
    assert(r->ival == 152);
    
    assert(parse_lizscript("  -6"));
    r = get_node(0);
    assert(r->type == LS_INT_T);
    assert(r->ival == -6);
    
    assert(parse_lizscript("+3.14"));
    r = get_node(0);
    assert(r->type == LS_FLOAT_T);
    assert(COMPARE_FLOAT(r->fval, 3.14));

    assert(!parse_lizscript("-..3"));
    assert(LSERR == EUNEXPECTEDTOKEN);

    // Test single char parsing
    assert(parse_lizscript("'c'"));
    r = get_node(0);
    assert(r->type == LS_CHAR_T);
    assert(r->cval == 'c');

    assert(parse_lizscript("')'"));
    r = get_node(0);
    assert(r->type == LS_CHAR_T);
    assert(r->cval == ')');

    // Test bool parsing
    assert(parse_lizscript("#t"));
    r = get_node(0);
    assert(r->type == LS_BOOL_T);
    assert(r->bval == true);

    assert(parse_lizscript("#f"));
    r = get_node(0);
    assert(r->type == LS_BOOL_T);
    assert(r->bval == false);

    assert(!parse_lizscript("#a"));
    assert(LSERR == EUNEXPECTEDTOKEN);

    // Test symbol parsing
    assert(parse_lizscript("foo"));
    r = get_node(0);
    assert(r->type == LS_SYMBOL_T);
    assert(strcmp(r->sym, "foo") == 0);

    assert(parse_lizscript("foo[4]"));
    r = get_node(0);
    assert(r->type == LS_SYMBOL_T);
    assert(strcmp(r->sym, "foo[4]") == 0);

    assert(parse_lizscript("*"));
    r = get_node(0);
    assert(r->type == LS_SYMBOL_T);
    assert(strcmp(r->sym, "*") == 0);
    
    return 0;
}
