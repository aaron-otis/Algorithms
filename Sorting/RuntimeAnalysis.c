#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "RandomListGenerator.h"
#include "SelectionSort.h"
#include "MergeSort.h"

#define MAX 10000
#define MIN -10000
#define STEP 20
#define SEC_PER_MIN 60

#define MEM_MULTIPLIER 10
#define FILENAME "Assignment1.csv"
#define MODE "w"

void PrintList(int *list, short size) {
    while (size--)
        printf("%d\n", *list++);
}

int main(int argc, char **argv) {
    unsigned short size = MAX;
    int *list, *mList;
    double runtime;
    clock_t start, stop;
    time_t begin, end;
    FILE *fp = fopen(FILENAME, MODE);
    MergeData data;

    begin = time(NULL);
    fprintf(fp, "Size,Selection Sort, Merge Sort\n");

    while (size <= 2 * MAX) {
        list = RandomListGenerator(MIN, MAX, size);
        mList = calloc(sizeof(int), size);
        memcpy(mList, list, size * sizeof(int));
        MergeDataInit(&data, mList, size); // Allocate list memory.

        // Time Selection Sort.
        start = clock();
        SelectionSort(&list, size);
        stop = clock();

        runtime = stop - start;
        fprintf(fp, "%d,%lf,", size, runtime / CLOCKS_PER_SEC);
        free(list);

        // Time Merge Sort.
        start = clock();
        list = MergeSort(&data, mList, size);
        stop = clock();

        runtime = stop - start;
        fprintf(fp, "%lf\n", runtime / CLOCKS_PER_SEC);
        MergeDataFree(&data, data->size);

        free(mList);
        size += STEP;
    }
    fclose(fp);
    end = time(NULL);
    runtime = end - begin;
    printf("\nProgram runtime: %.3lf minutes\n", runtime / SEC_PER_MIN);

    return 0;
}
