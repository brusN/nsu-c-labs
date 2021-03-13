#include "lab0header.h"

int main(int argc, char* argv[]) {

    int base1 = 0;
    int base2 = 0;
    char input[256];

    if (argc > 3) {
        base1 = atoi(argv[1]);
        base2 = atoi(argv[2]);
        int j = 0;
        while (argv[3][j] != 0) {
            input[j] = argv[3][j];
            ++j;
        }
        input[j] = 0;
    }
    else {
        if (scanf("%d %d", &base1, &base2) != 2) 
			exit(1);
        if (scanf("%14s", input) != 1) 
			exit(1);
    }

    if (!(base1 >= 2 && base1 <= 16 && base2 >= 2 && base2 <= 16)) {
        printf("bad input");
    }
    else {
        ConvertFunction(base1, base2, input);
    }

    return 0;
}
