#include <stdio.h>  
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define BUFF_SIZE 1024
#define PATTERN_SIZE 18
// lol
size_t readString(unsigned char* string, int count) {

    if (fgets((char*)string, count + 2, stdin) == 0) {
        return -1;
    }

    size_t lengthPattern = strlen((const char*)string); // длина шаблона

    if (--lengthPattern == 0) // если считана пустая строка
        exit(0);

    string[lengthPattern] = 0;
    return lengthPattern;
}

int main(void) {

	unsigned char *pattern = (unsigned char*)malloc(sizeof(unsigned char) * PATTERN_SIZE);// строка-шаблон
	size_t lengthPattern = readString(pattern, 16);
	size_t pointer = 0;

	int patternHashAmount = 0; // вычисляем хэш-сумму для шаблона
	for (size_t i = 0; i < lengthPattern; i++) {
		patternHashAmount += pattern[i] % 3 * (int)pow(3, i);
	}

	printf("%d ", patternHashAmount);

	unsigned char *buff = (unsigned char*)malloc(sizeof(unsigned char) * BUFF_SIZE);

    while (fgets((char*)buff, BUFF_SIZE, stdin) != NULL) {

        size_t lengthBuff = strlen((const char*)buff);

		if ((lengthBuff >= lengthPattern) && (buff[lengthBuff - 1] != '\n')) {
            int hashAmount = 0;
            size_t index = 0; // указатель на начало каретки
			for (size_t j = 0; j < lengthPattern; ++j)
				hashAmount += buff[j] % 3 * (int)pow(3, j);

			while (index < lengthBuff - lengthPattern + 1) {
				if (hashAmount == patternHashAmount) {
					for (size_t i = 0; i < lengthPattern; ++i) {
						printf("%zu ", pointer + index + i + 1);
						if (buff[index + i] != pattern[i])
							break;
					}
				}
				hashAmount = (hashAmount - buff[index] % 3 * (int)pow(3, 0)) / 3 + buff[index + lengthPattern] % 3 * (int)pow(3, (double)lengthPattern - 1);
				++index;
			}

		}
		pointer += lengthBuff;
	}


	free(buff);
	free(pattern);

	return 0;
}

