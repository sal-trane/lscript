#include <parser.h>
#include <progheap.h>
#include <stdio.h>

int main()
{
    size_t heap_size = sizeof(unsigned short int) * LS_HEAP_SIZE;
    size_t pool_size = sizeof(LSData) * LS_POOL_SIZE;

    printf("Heap Size: %ld bytes\nPool Size: %ld bytes\n",
        heap_size, pool_size);
    printf("Total: %.2f kB\n", (heap_size + pool_size) / 1024.0);
    return 0;
}
