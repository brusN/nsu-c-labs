#include <stdio.h>
#include <stdlib.h>

void quicksort(int* array, int point1, int point2) {
    if (point1 < point2)
    {
        int i = point1;
        int j = point2;
        int pivot = array[(i + j) / 2];
        do
        {
            while (array[i] < pivot)
                ++i;
            while (array[j] > pivot)
                --j;

            if (i <= j)
            {
                int box = array[i];
                array[i] = array[j];
                array[j] = box;
                ++i;
                --j;
            }
        } while (i <= j);

        if (j > 0)
            quicksort(array, point1, j);
        if (i < point2)
            quicksort(array, i, point2);
    }
}

int main(void) {

    size_t length;

    if (scanf("%zu", &length) == 0) {
        printf("input error");
        exit(0);
    }

    int* array = (int*)malloc(sizeof(int) * length);

    for (size_t i = 0; i < length; ++i)
        if (scanf("%d", &array[i]) == 0) {
            printf("input error");
            exit(0);
        }

    quicksort(array, 0, length - 1);

    for (size_t i = 0; i < length; ++i)
        printf("%d ", array[i]);

    free(array);

    return 0;
}


