#include <stdlib.h>
#include <time.h>
#include "RandomListGenerator.h"

int *RandomListGenerator(long min, long max, long size) {
    int i, *ret = calloc(sizeof(int), size);

    srand(time(NULL));
    for (i = 0; i < size; i++) {
        ret[i] = rand() + rand();
        ret[i] /= RAND_MAX / max + 1;
    }

    return ret;
}
