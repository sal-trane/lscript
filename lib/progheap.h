/*
 * progheap.h
 *
 * Defines the interface for interacting with the AST heap structure.
 */

#ifndef PROGHEAP_H
#define PROGHEAP_H

#define LS_HEAP_SIZE (1<<LS_HEAP_DEPTH)
#define LEFT(i) ((2 * i) + 1)
#define RIGHT(i) ((2 * i) + 2)

#include "types.h"

void set_program_root(LSData root);
int insert_left(int parent, LSData left);
int insert_right(int parent, LSData right);
LSData* get_node(int index);
LSData* get_left_child(int parent);
LSData* get_right_child(int parent);
void reset_progheap();

#endif
