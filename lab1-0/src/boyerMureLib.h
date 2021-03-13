#ifndef LAB1_0_BOYERMURELIB_H
#define LAB1_0_BOYERMURELIB_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFF_SIZE 1024
#define PATTERN_SIZE 18

void FillTable(unsigned int* table, const char* pattern_arr, size_t length_arr);
void PrintEntry(size_t* temp, size_t* j, size_t index);
void DoShift(const char* buff, const char* pattern, size_t length_pattern, size_t temp, size_t* point, size_t index, size_t j, const unsigned int* shift_table);
void BoyerMureAlg(const char* pattern, const unsigned int* shift_table, size_t length_pattern);

#endif //LAB1_0_BOYERMURELIB_H
