#ifndef LAB4_stackInt_HEADER_H
#define LAB4_stackInt_HEADER_H
#include <stdio.h>
#include <stdlib.h>
//  // 
typedef struct st_stackInt stackInt; // stackInt struct
struct st_stackInt {
    int key;
    stackInt* next;
};

typedef struct st_stackChar stackChar; // stackСhar struct
struct st_stackChar {
    char key;
    stackChar* next;
};

stackInt* initialStackInt();
stackChar *initialStackChar();
//

stackInt *createNewElemStackInt(int elem);

stackChar *createNewElemStackChar(char elem);

int popTopStackInt(stackInt *top);

char popTopStackChar(stackChar *top);

void pushTopStackInt(stackInt *top, stackInt *elem);

void pushTopStackChar(stackChar *top, stackChar *elem);

int isStackIntEmptyInt(stackInt* top);

int isStackIntEmptyChar(stackChar* top);

void cleanStackInt(stackInt *top);

void cleanStackChar(stackChar *top);

#endif //LAB4_stackInt_HEADER_H

