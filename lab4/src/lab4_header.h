#ifndef LAB4_LAB4_HEADER_H
#define LAB4_LAB4_HEADER_H
#define MAX_SIZE 1000
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stack_header.h"
// //  // 
size_t readString(char* string, size_t count, FILE *input);

int isOperation(char symbol);

int getPriority(char sym);

int doOperation(stackInt* numbers, stackChar* operations, char operation, char* input);

void printSyntaxErr(stackInt *numbers, stackChar *operations, char* input);

void findOpenBracket(stackInt *numbers, stackChar *operations, size_t index, char* input);

void checkSyntax(stackInt* numbers, stackChar* operations, char* input);

void calculateFunc(char* input, size_t length, stackInt *numbers, stackChar* operations);

#endif //LAB4_LAB4_HEADER_H

