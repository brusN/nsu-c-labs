#include "boyerMureLib.h"

void FillTable(unsigned int* table, const char* pattern_arr, size_t length_arr) { // Заполнение таблицы сдвигов

    size_t i = 0;

    for (i = 0; i < 256; ++i) {
        table[i] = length_arr;
    }

    if (length_arr > 0)
        for (i = 0; i < length_arr - 1; ++i) {
            table[(unsigned char)pattern_arr[i]] = length_arr - i - 1;
        }
}

void PrintEntry(size_t* temp, size_t* j, size_t index) { // Вывести индекс вхождения
    printf("%zu ", index + *temp + 1);
    --* temp;
    --* j;
}

void DoShift(const char* buff, const char* pattern, size_t length_pattern, size_t temp, size_t* point, size_t index, size_t j, const unsigned int* shift_table) { // Сделать сдвиг по строке
    if (j == length_pattern) {
        printf("%zu ", index + temp + 1);
        *point += (size_t)shift_table[(unsigned char)buff[temp]];
    }
    else if (j == 0) {
        *point += length_pattern;
    }
    else {
        printf("%zu ", index + temp + 1);
        *point += shift_table[(unsigned char)pattern[length_pattern - 1]];
    }
}

void BoyerMureAlg(const char* pattern, const unsigned int* shift_table, size_t length_pattern) { // Реализация алгоритма Бойера-Мура Хорспула

    char* buff = malloc(sizeof(char) * (BUFF_SIZE + 2));
    size_t j = length_pattern; // if j == 0 - шаблон найден
    size_t index = 0; // сдвиг по строкам

    while (fgets(buff, BUFF_SIZE, stdin) != NULL) {

        size_t len = strlen((const char* )buff);
        size_t point = length_pattern - 1;

        while (point < len) {
            j = length_pattern;
            size_t temp = point;

            while (j > 0 && pattern[j - 1] == buff[temp])
                PrintEntry(&temp,  &j, index);

            DoShift((const char*)buff, pattern, length_pattern, temp, &point, index, j, shift_table);
        }
        index += len; // сделать сдвиг на строку
    }
    free(buff);
}



