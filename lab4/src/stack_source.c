#include "stack_header.h"
//  // 
stackInt* initialStackInt() { //
    stackInt *newStack = malloc(sizeof(stackInt));
    newStack->key = 0;
    newStack->next = NULL;
    return newStack;
}

stackChar *initialStackChar() {
    stackChar *newStack = malloc(sizeof(stackChar));
    newStack->key = 0;
    newStack->next = NULL;
    return newStack;
}


stackInt *createNewElemStackInt(int elem) { // create a new element in number's stack
    stackInt* newElem = malloc(sizeof(stackInt));
    newElem->key = elem;
    newElem->next = NULL;
    return newElem;
}

stackChar *createNewElemStackChar(char elem) { // create a new element in operation's stack
    stackChar* newElem = malloc(sizeof(stackChar));
    newElem->key = elem;
    newElem->next = NULL;
    return newElem;
}

int popTopStackInt(stackInt *top) {
    int value = 0;
    stackInt *deleteElem = 0;
    if (top->next) {
        value = top->next->key;
        deleteElem = top->next;
        top->next = top->next->next;
    }
    free(deleteElem);
    deleteElem = NULL;
    return value;
}

char popTopStackChar(stackChar *top) {
    char value = 0;
    stackChar *deleteElem = 0;
    if (top->next) {
        value = top->next->key;
        deleteElem = top->next;
        top->next = top->next->next;
    }
    free(deleteElem);
    deleteElem = NULL;
    return value;
}

void pushTopStackInt(stackInt *top, stackInt *elem) {
    elem->next = top->next;
    top->next = elem;
}

void pushTopStackChar(stackChar *top, stackChar *elem) {
    elem->next = top->next;
    top->next = elem;
}

int isStackIntEmptyInt(stackInt* top) {
    if (top -> next == NULL)
        return 1;
    return 0;
}

int isStackIntEmptyChar(stackChar* top) {
    if (top -> next == NULL)
        return 1;
    return 0;
}

void cleanStackInt(stackInt *top) {
    stackInt *temp = top->next;
    while (temp) {
        stackInt *deletedNode = temp;
        temp = temp->next;
        free(deletedNode);
    }
    top->next = NULL;
    free(top);
    temp = NULL;
}

void cleanStackChar(stackChar *top) {
    stackChar *temp = top->next;
    while (temp) {
        stackChar *deletedNode = temp;
        temp = temp->next;
        free(deletedNode);
    }
    top->next = NULL;
    free(top);
    temp = NULL;
}

