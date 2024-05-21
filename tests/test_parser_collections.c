/*
 * Tests the parsing of collections (lists and expressions)
 */

#include <parser.h>
#include <progheap.h>
#include <errors.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

int test_list_element(int index, LSType type)
{
    LSData* node;
    int treeIndex = 0, i;
    for (i = 0; i < index; i++)
    {
        treeIndex = (treeIndex * 2) + 2;
    }
    node = get_node(treeIndex);
    if ((node->type & (LS_LIST_T | LS_FUNC_T)) == 0) return -1;
    node = get_left_child(treeIndex);
    if (node->type != type) return -2;
    return node->ival;
}

int main()
{
    LSData* res;

    // Test list of ints
    assert(parse_lizscript("`(1 2 3)"));
    assert(test_list_element(0, LS_INT_T) == 1);
    assert(test_list_element(1, LS_INT_T) == 2);
    assert(test_list_element(2, LS_INT_T) == 3);
    reset_progheap();

    // Test list of mixed atoms
    assert(parse_lizscript("`( 1 '2' -3.2 foo #f )"));
    assert(test_list_element(0, LS_INT_T) == 1);
    assert(test_list_element(1, LS_CHAR_T) == '2');
    test_list_element(2, LS_FLOAT_T);
    test_list_element(3, LS_SYMBOL_T);
    assert(test_list_element(4, LS_BOOL_T) == false);
    reset_progheap();

    // Test list including a list
    assert(parse_lizscript("`(1 `(2) 3)"));
    assert(test_list_element(0, LS_INT_T) == 1);
    test_list_element(1, LS_LIST_T);
    assert(test_list_element(2, LS_INT_T) == 3);
    reset_progheap();

    // Test expression with single arg
    assert(parse_lizscript("(foo 5)"));
    res = get_node(0);
    assert(res->type == LS_FUNC_T);
    assert(strcmp(res->sym, "foo") == 0);
    assert(test_list_element(0, LS_INT_T) == 5);
    reset_progheap();

    // Test deeply nested expression
    assert(parse_lizscript("(let `(`(n 5) `(k 3)) (* n (+ k 3))"));

    return 0;
}
