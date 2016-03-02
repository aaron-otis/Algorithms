#include "SelectionSort.h"

void SelectionSort(int **list, long size) {
    int temp, i, j, pos;

    for (i = 0; i < size; i++) {
        pos = i;
        temp = (*list)[i];

        for (j = i + 1; j < size; j++) {
            if ((*list)[j] < temp) {
                temp = (*list)[j];
                pos = j;
            }
        }
        if (pos > i) {
            (*list)[pos] = (*list)[i];
            (*list)[i] = temp;
        }
    }
}
