#include "lab4_header.h"//
//  // 
size_t readString(char* string, size_t count, FILE *input) { // read string with checking
    if (fgets(string, count + 1, input) == NULL) {
        return 0;
    }
    size_t length = strlen(string);
    if (string[length - 1] == '\n') {
        string[length--] = 0;
    }
    return length;
}

int isOperation(char symbol) {
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' ||  symbol == '(' || symbol == ')')
        return 1;
    return 0;
}

int getPriority(char sym) { // returns operation's priority
    switch(sym) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 0;
    }
}

int doOperation(stackInt* numbers, stackChar* operations, char operation, char* input) { // do operation with num1 && num2
    switch(operation) {
        case '+':
            return popTopStackInt(numbers->next) + popTopStackInt(numbers);
        case '-':
            return  popTopStackInt(numbers->next) - popTopStackInt(numbers);
        case '*':
            return  popTopStackInt(numbers->next) * popTopStackInt(numbers);
        case '/':
            if ((numbers->next -> key) == 0) {
                printf("division by zero");
                free(input);
                cleanStackInt(numbers);
                cleanStackChar(operations);
                exit(0);
            } else return  popTopStackInt(numbers->next) / popTopStackInt(numbers);
        default:
            printSyntaxErr(numbers, operations, input);
            return 1;
    }
}


void printSyntaxErr(stackInt *numbers, stackChar *operations, char* input) {
    free(input);
    cleanStackInt(numbers);
    cleanStackChar(operations);
    printf("syntax error");
    exit(0);
}

void findOpenBracket(stackInt *numbers, stackChar *operations, size_t index, char* input) {
    stackChar *temp = operations -> next;
    if (index == 0)
        printSyntaxErr(numbers, operations, input);

    while (temp && temp->key != '(') {
        temp = temp -> next;
    }
    if (temp == NULL || input[index - 1] == '(')
        printSyntaxErr(numbers, operations, input);
    temp = NULL;
}

void checkSyntax(stackInt* numbers, stackChar* operations, char* input) {
    if (numbers -> next == NULL || numbers -> next -> next == NULL)
        printSyntaxErr(numbers, operations, input);

}


void calculateFunc(char* input, size_t length, stackInt *numbers, stackChar* operations) {
    for (size_t i = 0; i < length; ++i) {

        if (isdigit(input[i])) {
            int num = input[i] - '0';

            while ((isdigit(input[++i])) && (i < length)) {
                num = num * 10 + (input[i] - '0');
            }
            i--;
            pushTopStackInt(numbers, createNewElemStackInt(num));

        } else if (isOperation(input[i])) {
            if (isStackIntEmptyChar(operations) && input[i] != '(' && input[i] != ')') {
                pushTopStackChar(operations, createNewElemStackChar(input[i]));
            } else {
                if (input[i] == '(') {
                    pushTopStackChar(operations, createNewElemStackChar(input[i]));
                } else if (input[i] == ')') {
                    findOpenBracket(numbers, operations, i, input); // ошибка тут, i == 0
                    while (operations->next->key != '(') {
                        checkSyntax(numbers, operations, input);
                        pushTopStackInt(numbers, createNewElemStackInt(doOperation(numbers, operations, operations->next->key, input)));
                        popTopStackChar(operations);
                    }
                    popTopStackChar(operations);
                } else if (getPriority(input[i]) > getPriority(operations->next->key)) {
                    pushTopStackChar(operations, createNewElemStackChar(input[i]));
                } else {
                    if (!isStackIntEmptyInt(numbers)) {
                        checkSyntax(numbers, operations, input);
                        pushTopStackInt(numbers, createNewElemStackInt(doOperation(numbers, operations, operations->next->key, input)));
                        popTopStackChar(operations);
                        pushTopStackChar(operations, createNewElemStackChar(input[i]));
                    } else {
                        printSyntaxErr(numbers, operations, input);
                    }
                }
            }
        } else {
            printSyntaxErr(numbers, operations, input);
        }
    }

    if(isStackIntEmptyInt(numbers)){
        printf("syntax error");
    } else {
        while(!isStackIntEmptyChar(operations)){
            checkSyntax(numbers, operations, input);
            pushTopStackInt(numbers, createNewElemStackInt(doOperation(numbers,  operations, operations->next-> key, input)));
            popTopStackChar(operations);
        }
        printf("%d", numbers->next->key);
        popTopStackInt(numbers);
    }
}

