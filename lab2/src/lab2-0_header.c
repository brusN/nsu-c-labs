#include "lab2-0_header.h"
#include <string.h>
#include <stdlib.h>

void reverseString(char* string, size_t point1, size_t point2) {
	if (point2 < point1) {
		printf("error");
		exit(0);
	}

	size_t i = point1, j = point2;
	while (i < j) {
		char box = string[i];
		string[i] = string[j];
		string[j] = box;
		i++;
		j--;
	}

}

int checkRightInput(char* input) {

	size_t tableNumbers[10];
	size_t length = strlen(input);

	for (size_t i = 0; i < 10; ++i) {
		tableNumbers[i] = 0;
	}

	for (size_t i = 0; i < length; ++i) {
		++tableNumbers[input[i] - '0'];
		if (!(input[i] >= '0' && input[i] <= '9')) {
			printf("bad input");
			exit(0);
		}

	}

	for (size_t i = 0; i < 10; ++i) {
		if (tableNumbers[i] > 1) {
			return -1;
		}
	}
	return 1;
}

int checkLastPermutation(char* permutation) {
	size_t length = strlen(permutation);
	for (size_t i = 0; i < length - 1; ++i) {
		if (permutation[i] <= permutation[i + 1])
			return -1;
	}
	return 1;
}

void makeNewPermutation(char* basicPermutation, size_t count) {
	size_t k = 0;
	while (k < count&& checkLastPermutation(basicPermutation) != 1) {
		size_t lengthPermutation = strlen(basicPermutation);

        for (size_t i = lengthPermutation - 1; i > 0; --i) {
			if (basicPermutation[i] > basicPermutation[i - 1]) {
				size_t pivot = i;
				for (size_t j = pivot; j < lengthPermutation; j++) {
					if ((basicPermutation[j] <= basicPermutation[pivot]) && (basicPermutation[j] > basicPermutation[i - 1])) {
						pivot = j;
					}
				}

				char box = basicPermutation[i - 1];
				basicPermutation[i - 1] = basicPermutation[pivot];
				basicPermutation[pivot] = box;

				reverseString(basicPermutation, i, lengthPermutation - 1);
				printf("%s\n", basicPermutation);
				++k;
				break;
			}
		}
	}
}

