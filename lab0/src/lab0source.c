#include "lab0header.h"

void SwapFunc(char* t1, char* t2) // Поменять символы значениями
{
    char t;
    t = *t1;
    *t1 = *t2;
    *t2 = t;
}

void ReverseString(char inputstring[], int Length) { // Реверс строки
    for (int i = 0; i < Length / 2; ++i) {
        SwapFunc(&inputstring[i], &inputstring[Length - i - 1]);
    }
}

int CharToInt(char c, int p1) { // Перевод символа в число
    int x;
    if (isdigit(c)) {
        x = c - '0';
    }
    else {
        c = tolower(c);
        x = c - 'a' + 10;
    }

    if (!(x >= 0 && x < p1)) {
        printf("bad input");
        exit(0);
    }

    return x;
}

char IntToChar(int x, int p1) // Перевод числа в символ
{
    if (!(x >= 0 && x < p1)) {
        printf("bad input");
        exit(0);
    }
    if (x > 9) {

        x = x + 'a' - 10;
    }
    else {
        x = x + '0';
    }
    return x;
}

void ConvertFunction(int base1f, int base2f, char inputf[]) {

    if (inputf[0] == '.' || inputf[0] == ',') {
        printf("bad input");
        exit(0);
    }

    long long whole = 0; // целая часть
    size_t i = 0;

    while (inputf[i] != '.' && inputf[i] != ',' && inputf[i] != 0) { // Записываем в whole целую часть в 10 СС.
        whole = whole * base1f + CharToInt(inputf[i], base1f);
        ++i;
    }


    char wholepart[256];
    if (whole == 0) {
        wholepart[0] = '0';
        wholepart[1] = 0;
    }
    else {

        size_t j = 0;
        while (whole > 0) { // Записываем в строку wholepart число в нужную СС.
            wholepart[j] = IntToChar(whole % base2f, base2f);
            whole /= base2f;
            ++j;
        }
        wholepart[j] = 0;
        ReverseString(wholepart, j);
    }

    if (inputf[i] == 0) { // Если дробной части нет

        printf("%s\n", wholepart);
    }
    else { // Если дробная часть есть

        int k = 0; // Степень основания СС.
        ++i; // Переходим от "." or "," к дробной части
        if (inputf[i] == 0) {
            printf("bad input");
            exit(0);
        }

        double fract = 0; // дробная часть

        while (inputf[i] != 0) { // Записываем в fract дробную часть в 10 СС.
            --k;
            fract = fract + (double)CharToInt(inputf[i], base1f) * pow(base1f, k);
            ++i;
        }

        char fractpart[16];

        i = 0;
        while (fract != 0 && i < 12) { // Записываем в строку fractpart дробную часть в нужную СС. до 12 символов
            fract *= base2f;
            fractpart[i] = IntToChar((int)trunc(fract), base2f);
            fract -= (double)trunc(fract);
            ++i;
        }
        fractpart[i] = 0;

        printf("%s.%s", wholepart, fractpart);

    }
}
