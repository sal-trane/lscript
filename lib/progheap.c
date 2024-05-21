#include "progheap.h"
#include "errors.h"
#include "config.h"

LSData pool[LS_POOL_SIZE];
unsigned short int progheap[LS_HEAP_SIZE + 1];
int poolCounter;

int insert_node(LSData node)
{
    switch (node.type)
    {
        case LS_INVALID_T:
            return 0;
        case LS_LIST_T:
            return 1;
        default:
            pool[poolCounter] = node;
            return poolCounter++;
    }
}

/*
 * Public functions
 */
void set_program_root(LSData root)
{
    //reset the pool
    poolCounter = 2;
    pool[0] = LS_NULL;
    pool[1] = (LSData) { .type = LS_LIST_T };
    progheap[0] = insert_node(root);
}

int insert_left(int parent, LSData left)
{
    int index = LEFT(parent);
    if (poolCounter >= LS_POOL_SIZE)
    {
        LSERR = EHEAPOVERFLOW;
        return -1;
    }
    progheap[index] = insert_node(left);
    LSERR = NOERR;
    return index;
}

int insert_right(int parent, LSData right)
{
    int index = RIGHT(parent);
    if (poolCounter >= LS_POOL_SIZE)
    {
        LSERR = EHEAPOVERFLOW;
        return -1;
    }
    progheap[index] = insert_node(right);
    LSERR = NOERR;
    return index;
}

LSData* get_node(int index)
{
    if (index < 0 || index >= LS_HEAP_SIZE
        || progheap[index] < 0 || progheap[index] >= LS_POOL_SIZE)
    {
        LSERR = ENOTFOUND;
        return &pool[0];
    }
    LSERR = NOERR;
    return &pool[progheap[index]];
}

LSData* get_left_child(int parent)
{
    return get_node(LEFT(parent));
}

LSData* get_right_child(int parent)
{
    return get_node(RIGHT(parent));
}

void reset_progheap()
{
    int i;
    for (i = 0; i < LS_HEAP_SIZE; i++)
    {
        progheap[i] = -1;
    }
}
