#include "myMem.h"

static char HEAP[HEAP_SIZE];
char* freep = HEAP;

char* my_allocate(unsigned int size) {
        char* ret = freep;
        freep += size + 1;

        return ret;
}

void free_all() {
        freep = HEAP;
        return;
}

