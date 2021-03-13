#include <stdio.h>
#include <stdlib.h>

void heapify(int array[], int length, int index) {
	int max = index;
	int leftLeaf = 2 * index + 1;
	int rightLeaf = 2 * index + 2;

	if (leftLeaf < length && array[leftLeaf] > array[max])
		max = leftLeaf;

	if (rightLeaf < length && array[rightLeaf] > array[max])
		max = rightLeaf;

	if (max != index) {
		int box = array[index];
		array[index] = array[max];
		array[max] = box;
		heapify(array, length, max);
	}
}

void heapSort(int array[], int length) {
	for (int i = length / 2 - 1; i >= 0; i--)
		heapify(array, length, i);

	for (int i = length - 1; i >= 0; i--) {
		int box = array[0];
		array[0] = array[i];
		array[i] = box;
		heapify(array, i, 0);
	}

}


int main(void) {

	int length;
	if (scanf("%d", &length) == 0) {
		printf("bad input");
		exit(0);
	}

	int *array = (int*)malloc(sizeof(int) * length);
	
	for (int i = 0; i < length; ++i) {
		if (scanf("%d", &array[i]) == 0) {
			printf("bad input");
			exit(0);
		}
	}

	heapSort(array, length);
	
	for (int i = 0; i < length; ++i) {
		printf("%d ", array[i]);
	}

	free(array);

	return 0;
}

