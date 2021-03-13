#include <stdio.h>
#include "lab4_header.h"
 // 

int main(void) { 

    FILE *input = fopen("in.txt", "r"); // open in.txt

    char *inputString = malloc(sizeof(char) * MAX_SIZE + 2); // input string
    size_t length = readString(inputString, MAX_SIZE, input);
    fclose(input);

    if (length == 0) { // check input
        printf("syntax error");
        free(inputString);
        exit(0);
    }

    stackInt *numbers = initialStackInt();
    stackChar *operations= initialStackChar();

    calculateFunc(inputString, length, numbers, operations);

    free(inputString);
    inputString = NULL;
    cleanStackChar(operations);
    cleanStackInt(numbers);

    return 0;
}

