#include <stdio.h>
#include "huffmanHeader.h"
#define ENCODE_DATA_MODE 'c'
#define DECODE_DATA_MODE 'd'

int main(void) {

    FILE* input = openFile("in.txt", "rb");

    char mode[4];
    if (fgets(mode, 3, input) == 0)
        printError();

    if (mode[0] == ENCODE_DATA_MODE) {
        FILE* output = openFile("out.txt", "wb");
        encode(input, output); // input file and output file paths
        closeFiles(input, output);
    }
    else if (mode[0] == DECODE_DATA_MODE) {
        FILE* output = openFile("out.txt", "wb");
        decode(input, output); // input file and output file paths // for decode test
        closeFiles(input, output);
    }
    else {
        printf("Wrong input\n");
        fclose(input);
        exit(1);
    }

    return 0;
}

