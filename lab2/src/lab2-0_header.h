#pragma once
#include <stdio.h>	
#include <string.h>
#include <stdlib.h>

void reverseString(char* string, size_t point1, size_t point2);
int checkRightInput(char* input);
int checkLastPermutation(char* permutation);
void makeNewPermutation(char* basicPermutation, size_t count);

