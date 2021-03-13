#include "lab2-0_header.h"
#include <string.h>

int main(void) {

	char basicPermutation[11]; //   
	if (scanf("%10s", basicPermutation) == 0) {
		printf("bad input");
		exit(0);
	}

	size_t count; //    
	if (scanf("%zu", &count) == 0) {
		printf("bad input");
		exit(0);
	}

	if (checkRightInput(basicPermutation) < 0) { //     
		printf("bad input");
		exit(0);
	}

	makeNewPermutation(basicPermutation, count);
	return 0;
}


