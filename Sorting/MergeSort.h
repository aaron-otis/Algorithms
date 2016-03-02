#ifndef MERGESORT_H
#define MERGESORT_H


typedef struct MergeData {
    int **data;
    long size;
    long pos;
} MergeData;

int *MergeSort(MergeData *data, int *list, long size);
void MergeDataInit(MergeData *data, int *list, long size);
void MergeDataFree(MergeData *data, long size);

#endif
