#include "boyerMureLib.h"
// 

int main(void) {

    char* pattern = malloc(sizeof(char) * PATTERN_SIZE); // строка с шаблоном
    size_t length_pattern = 0; // длина шаблона

    if (fgets(pattern, PATTERN_SIZE, stdin) == NULL)
        exit(0);

    length_pattern = strlen(pattern) - 1;
    pattern[length_pattern] = 0;


    unsigned int shift_table[256]; // таблица сдвигов
    FillTable(shift_table, (const char* )pattern, length_pattern); // заполняем таблицу сдвигов

    BoyerMureAlg((const char* )pattern, (const unsigned int*)shift_table, length_pattern);
    
    free(pattern);
    return 0;

}
