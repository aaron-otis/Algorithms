#include <stdlib.h>
#include <string.h>
#include "MergeSort.h"
#include <stdio.h>

static int *Merge(MergeData *data, int *lhs, int *rhs, long lSize, long rSize) {
    int *temp, *ret = data->data[data->pos++];

    if (!lSize)
        memcpy(ret, rhs, rSize * sizeof(int));
    else if (!rSize)
        memcpy(ret, lhs, lSize * sizeof(int));
    else if (*lhs <= *rhs) {
        *ret = *lhs;
        temp = Merge(data, lhs + 1, rhs, --lSize, rSize);
        printf("n: %ld\n", lSize + rSize);
        memcpy(ret + 1, temp, (lSize + rSize) * sizeof(int));
    }
    else {
        *ret = *rhs;
        temp = Merge(data, lhs, rhs + 1, lSize, --rSize);
        printf("n: %ld\n", lSize + rSize);
        memcpy(ret + 1, temp, (lSize + rSize) * sizeof(int));
    }

    return ret;
}

int *MergeSort(MergeData *data, int *list, long size) {
    int *ret, *lhs, *rhs;

    if (size == 1) {
        ret = data->data[data->pos++];
        *ret = *list;
    }
    else {
        lhs = MergeSort(data, list, size / 2);
        rhs = MergeSort(data, list + size / 2, size - size / 2);
        ret = Merge(data, lhs, rhs, size / 2, size - size / 2);
    }

    return ret;
}

// Implementation of Merge() that helps determines how many dynamic allocations
// are created and also creates dynamic memory allocations.
static int *Smerge(MergeData *data, int *lhs, int *rhs, long lSize, long rSize,
 long *mSize, int alloc) {
    int *temp, *ret = calloc(sizeof(int), lSize + rSize);

    if (alloc)
        data->data[data->pos++] = ret;
    else
        *mSize += 1;

    if (!lSize)
        memcpy(ret, rhs, rSize * sizeof(int));
    else if (!rSize)
        memcpy(ret, lhs, lSize * sizeof(int));
    else if (*lhs <= *rhs) {
        *ret = *lhs;
        temp = Smerge(data, lhs + 1, rhs, --lSize, rSize, mSize, alloc);
        memcpy(ret + 1, temp, (lSize + rSize) * sizeof(int));
    }
    else {
        *ret = *rhs;
        temp = Smerge(data, lhs, rhs + 1, lSize, --rSize, mSize, alloc);
        memcpy(ret + 1, temp, (lSize + rSize) * sizeof(int));
    }
    if (!alloc && rSize && lSize)
        free(temp);

    return ret;
}

// Implementation of MergeSort() that help finds how many dynamically allocated
// memory blocks are needed as well as dynamically allocating said blocks.
static int *FindSize(MergeData *data, int *list, long size, long *mSize, 
 int alloc) {
    int *ret, *lhs, *rhs;

    if (size == 1) {
        ret = calloc(sizeof(int), 1);
        *ret = *list;
        if (alloc)
            data->data[data->pos++] = ret;
        else
            *mSize += 1;
    }
    else {
        lhs = FindSize(data, list, size / 2, mSize, alloc);
        rhs = FindSize(data, list + size / 2, size - size / 2, mSize, alloc);
        ret = Smerge(data, lhs, rhs, size / 2, size - size / 2, mSize, alloc);

        if (!alloc) {
            free(lhs);
            free(rhs);
        }
    }

    return ret;
}

void MergeDataInit(MergeData *data, int *list, long size) {

    data->size = 0;
    data->pos = 0;
    free(FindSize(data, list, size, &data->size, 0));

    data->data = calloc(sizeof(int *), data->size);
    FindSize(data, list, size, &data->size, 1);
    data->pos = 0;
}

void MergeDataFree(MergeData *data, long size) {
    int i;

    for (i = 0; i < size; i++)
        free(data->data[i]);
    free(data->data);
}
