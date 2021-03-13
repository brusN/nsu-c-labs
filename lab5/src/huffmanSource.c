#include "huffmanHeader.h"

// main functions

void clearTree(Tree* root) {
    if (root->link[0])
        clearTree(root->link[0]);
    if (root->link[1])
        clearTree(root->link[1]);
    free(root);
}

void printError() {
    printf("Wrong input\n");
    exit(1);
}

FILE* openFile(const char *filePath, const char *mode) {
    FILE* file;
    if ((file = fopen(filePath, mode)) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    return file;
}

void closeFiles(FILE* file1, FILE* file2) {
    fclose(file1);
    fclose(file2);
}

// basic functions

void resetTable(FreqTable *table) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        table[i].symbol = 0;
        table[i].freq = 0;
    }
}

void fillFreqTable(FreqTable *freqTable, size_t *totalLength, FILE *input) {
    size_t frag;
    unsigned char buff[BUFF_SIZE]; // buffer for reading parts of text
    frag = fread(buff, sizeof(char), BUFF_SIZE, input);

    while (frag) {
        for (size_t i = 0; i < frag; ++i) {
            freqTable[buff[i]].symbol = buff[i];
            ++freqTable[buff[i]].freq;
        }

        *totalLength += frag;
        frag = fread(buff, sizeof(char), BUFF_SIZE, input);
    }
}

void stableSortFreqTable(FreqTable *freqTable) {
    for (size_t i = 0; i < TABLE_SIZE - 1; ++i) {
        size_t min = i;
        for (size_t j = i + 1; j < TABLE_SIZE; ++j) {
            if (freqTable[j].freq < freqTable[min].freq)
                min = j;
        }

        if (min != i) {
            FreqTable box;
            box = freqTable[i];
            freqTable[i] = freqTable[min];
            freqTable[min] = box;
        }
    }
}

size_t findFirstNonZeroFreq(FreqTable *table) {
    for (size_t index = 0; index < TABLE_SIZE; ++index) {
        if (table[index].freq != 0) {
            return index;
        }
    }
    return NOT_FOUND;
}

// single-linked list functions

Tree *initNewTree(FreqTable value) {
    Tree *newElem = malloc(sizeof(Tree));
    newElem->link[0] = NULL;
    newElem->link[1] = NULL;
    newElem->value = value;
    return newElem;
}

listFreq *initNewElemListFreq(FreqTable value) {
    listFreq *newElem = malloc(sizeof(listFreq));
    newElem->next = NULL;
    newElem->leaf = initNewTree(value);
    return newElem;
}

void addElemListFreq(listFreq **root, listFreq *elem) {
    elem->next = *root;
    *root = elem;
}

listFreq *createListFreq(listFreq *root, FreqTable *table, int index) {
    root = initNewElemListFreq(table[TABLE_SIZE - 1]);
    for (int i = TABLE_SIZE - 2; i >= index; --i) {
        listFreq *box = initNewElemListFreq(table[i]);
        addElemListFreq(&root, box);
    }

    return root;
}

Tree* removeTopList(listFreq **top) { // проверить очистку памяти
    listFreq *temp = *top;
    Tree* deletedValue = initNewTree(temp->leaf->value);
    deletedValue->link[0] = temp->leaf->link[0];
    deletedValue->link[1] = temp->leaf->link[1];
    *top = temp->next;
    free(temp);
    return deletedValue;
}

// HUFFMAN TREE FUNCTIONS

Tree *createNewNode(listFreq *list) { // переделать
    Tree *newNode = malloc(sizeof(Tree));
    newNode->value.freq = list->leaf->value.freq + list->next->leaf->value.freq;
    newNode->link[0] = removeTopList(&list);
    newNode->link[1] = removeTopList(&list);
    newNode->value.symbol = 0;
    return newNode;
}

listFreq *insertNewElemList(listFreq *list) {
    FreqTable newValue;
    newValue.symbol = 0;
    newValue.freq = list->leaf->value.freq + list->next->leaf->value.freq;

    listFreq *newElem = initNewElemListFreq(newValue);

    listFreq *box = list;
    while (box->next->next != NULL && newElem->leaf->value.freq > box->next->next->leaf->value.freq)
        box = box->next; // переделать вставку

    newElem->next = box->next->next;
    box->next->next = newElem;

    newElem->leaf->link[0] = removeTopList(&list); // left leaf
    newElem->leaf->link[1] = removeTopList(&list); // right leaf
    return list;
}

Tree *createHuffmanTree(listFreq *rootList) {
    while (rootList->next->next != NULL)
        rootList = insertNewElemList(rootList);

    Tree *huffmanTree = createNewNode(rootList);
    return huffmanTree;

}

// Code table functions

void resetCodeTable (codeTable * table) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        table[i].code = NULL;
        table[i].length = 0;
    }
}

void findCode(Tree* huffmanTree, codeTable tableCode[TABLE_SIZE], unsigned char code[TABLE_SIZE], size_t level) {
    if (huffmanTree->link[0] && huffmanTree->link[1]) {
        code[level] = '0';
        findCode(huffmanTree->link[0], tableCode, code, level + 1);
        code[level] = '1';
        findCode(huffmanTree->link[1], tableCode, code, level + 1);
    }
    else {
        tableCode[huffmanTree->value.symbol].length = level;
        tableCode[huffmanTree->value.symbol].code = (unsigned char*)malloc(level + 1);
        memcpy(tableCode[huffmanTree->value.symbol].code, code, level);
        tableCode[huffmanTree->value.symbol].code[level] = 0;
    }
}

void fillCodeTable(Tree* huffmanTree, codeTable* codeTable) {
    unsigned char code[TABLE_SIZE];
    memset(code, 0,  TABLE_SIZE);
    findCode(huffmanTree, codeTable, code, 0);
}

void writeLengthOfMessage(int *length, FILE* output) {
    fwrite(&length, 1, 4, output);
}

void write1Bite(unsigned char* byte, size_t *k, unsigned char bite, FILE* output) {
    *byte = *byte * 2 + bite;
    ++*k;
    if (*k >= BYTE_SIZE) {
        fprintf(output, "%c", *byte); //
        *k = 0;
        *byte = 0;
    }
}

static int getBit(unsigned char byte) {
    return byte / 128;
}

void write8Bite(Tree* huffmanTree, unsigned char *byte, size_t *k, FILE* output) { // Подавать символ вместо дерева
    unsigned char symbol = huffmanTree->value.symbol;
    size_t count = 0;

    while (count < BYTE_SIZE && *k < BYTE_SIZE) {
        *byte = *byte * 2 + getBit(symbol);
        symbol = symbol << 1;
        ++*k;
        ++count;
    }
    if (*k >= BYTE_SIZE) {
        fputc(*byte, output);
        *byte = 0;
        *k = 0;
        while (count < BYTE_SIZE) {
            *byte = *byte * 2 + getBit(symbol);
            symbol = symbol << 1;
            ++*k;
            ++count;
        }
    }
}

void encodeTree(Tree* huffmanTree, unsigned char* byte, size_t *k, size_t *levelMax, size_t *level, FILE* output) {
    if (huffmanTree->link[0] != NULL || huffmanTree->link[1] != NULL) {
        /*++*level;
        if (*level > *levelMax) {
            *levelMax = *level;
        }*/

        write1Bite(byte, k, 1, output);
        //if (huffmanTree->link[0] != NULL)
        encodeTree(huffmanTree->link[0], byte, k, levelMax, level, output);

        //if (huffmanTree->link[1] != NULL)
        encodeTree(huffmanTree->link[1], byte, k, levelMax, level, output);

    } else {
        write1Bite(byte, k, 0, output);
        write8Bite(huffmanTree, byte, k, output);
    }
}

void encodeData(Tree* huffmanTree, codeTable *table, FILE* input, FILE* output) {
    unsigned char byte = 0;
    size_t k = 0; // bitPos

    size_t levelMax = 0;
    size_t level = 0;

    encodeTree(huffmanTree, &byte, &k, &levelMax, &level, output); // encode and print tree

    size_t codePos = 0;
    size_t buffPos = 0;
    unsigned char buff[BUFF_SIZE]; // buffer for reading
    size_t length = fread(buff, 1, BUFF_SIZE, input);

    while (length) {
        while (buffPos < length) {
            while (table[buff[buffPos]].code[codePos] != 0 && k < BYTE_SIZE) {
                byte = byte * 2 + (table[buff[buffPos]].code[codePos] - '0');
                ++k;
                ++codePos;
            }
            if (k >= BYTE_SIZE) {
                fprintf(output, "%c", byte);
                byte = 0;
                k = 0;
            } else {
                codePos = 0;
                buffPos++;
            }
        }
        buffPos = 0;
        length = fread(buff, 1, BUFF_SIZE, input);
    }

    if (k > 0) {
        while (k < BYTE_SIZE) {
            byte = byte << 1;
            ++k;
        }
        fputc(byte, output);
        k = 0;
        byte = 0;
    }
}

void clearTableOfCodes(codeTable* table) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        if (table[i].code != NULL) {
            free(table[i].code);
        }
    }
}

void encode(FILE* input, FILE* output) {
    size_t totalLength = 0; // Full data length
    fseek(input, 1, SEEK_CUR);
    size_t dataPos = ftell(input);

    FreqTable freqTable[TABLE_SIZE]; // Create a frequency table
    resetTable(freqTable); // Fill the frequency table with zeros
    fillFreqTable(freqTable, &totalLength, input); // Fill the frequency table
    stableSortFreqTable(freqTable); // Sort frequency table by using simple stable sort

    size_t index = NOT_FOUND; // index first non-zero freq
    if ((index = findFirstNonZeroFreq(freqTable)) == NOT_FOUND) { // if file is empty
        return;
    }

    Tree* huffmanTree = NULL;
    if ((TABLE_SIZE - index) == 1) {
        huffmanTree = initNewTree(freqTable[index]);
    } else {
        listFreq* list = malloc(sizeof(listFreq));
        list = createListFreq(list, freqTable, (int)index);
        huffmanTree = createHuffmanTree(list);
    }

    codeTable tableOfCodes[TABLE_SIZE];
    resetCodeTable(tableOfCodes);
    fillCodeTable(huffmanTree, tableOfCodes);

    fseek(input, dataPos, 0);
    writeLengthOfMessage((int*)(totalLength), output);
    encodeData(huffmanTree, tableOfCodes, input, output);

    clearTree(huffmanTree);
    clearTableOfCodes(tableOfCodes);
}

size_t readLengthOfMessage(FILE* input) {
    size_t length = 0;

    unsigned char buff[4];
    if (fread(buff, 1, 4, input) == 0) {
        printf("Error of reading!\n");
        exit(1);
    }

    for (size_t i = 0; i < 4; ++i) {
        int box = (int)buff[i];
        length = length + (box << (i * BYTE_SIZE));
    }
    return length;
}

unsigned char readSymbol(FILE* input, unsigned char *buff, size_t *bufPos, size_t *k, size_t *lengthBuff) {
    unsigned char symbol = 0;
    size_t count = 0;
    while (*k < BYTE_SIZE && count < BYTE_SIZE) {
        symbol = symbol * 2 + getBit(buff[*bufPos]);
        buff[*bufPos] = buff[*bufPos] << 1;
        ++*k;
        ++count;
    }
    if (*k >= BYTE_SIZE) {
        ++*bufPos;
        *k = 0;
        if (*bufPos >= *lengthBuff) {
            *bufPos = 0;
            *lengthBuff = fread(buff, 1, 16, input);
        }
        while (count < BYTE_SIZE) {
            symbol = symbol * 2 + getBit(buff[*bufPos]);
            buff[*bufPos] = buff[*bufPos] << 1;
            ++*k;
            ++count;
        }
    }
    return symbol;
}

void doShift(FILE* input, unsigned char* buff, size_t* k, size_t* bufPos, size_t* lengthBuff) {
    ++*k;
    buff[*bufPos] = buff[*bufPos] << 1;
    if (*k >= BYTE_SIZE) {
        ++*bufPos;
        *k = 0;
        if (*bufPos >= *lengthBuff) {
            *bufPos = 0;
            *lengthBuff = fread(buff, 1, 16, input);
        }
    }
}

void fillLeaf(Tree* leaf, unsigned char symbol) {
    leaf->value.symbol = symbol;
    leaf->value.freq = 1;
    leaf->link[0] = NULL;
    leaf->link[1] = NULL;
}

Tree* buildTree(FILE *input, unsigned char* buff, size_t *k, size_t *bufPos, size_t *lengthBuff) {
    Tree* newHuffmanTree = (Tree*)malloc(sizeof(Tree));
    if (getBit(buff[*bufPos]) == 1) {
        doShift(input, buff, k, bufPos, lengthBuff);
        newHuffmanTree->value.freq = 0;
        newHuffmanTree->value.symbol = 0;
        newHuffmanTree->link[0] = buildTree(input, buff, k, bufPos, lengthBuff);
        newHuffmanTree->link[1] = buildTree(input,  buff, k, bufPos, lengthBuff);
    } else
    {
        doShift(input, buff, k, bufPos, lengthBuff);
        unsigned char symbol = readSymbol(input, buff, bufPos, k, lengthBuff);
        fillLeaf(newHuffmanTree, symbol);
    }
    return newHuffmanTree;
}

void decodeData(FILE *input, FILE* output, Tree* newHuffmanTree, unsigned char* buff, size_t *k, size_t *bufPos, size_t *lengthBuff, size_t *countOfSymbols) {
    while (newHuffmanTree->link[0] || newHuffmanTree->link[1]) {
        newHuffmanTree = newHuffmanTree->link[getBit(buff[*bufPos])];
        doShift(input, buff, k, bufPos, lengthBuff);
    }

    fputc(newHuffmanTree->value.symbol, output);
    ++*countOfSymbols;
}

long int isEmptyFile(FILE* file) {
    if (file == NULL)
        return 1;

    long int pos = ftell(file);
    fseek(file, 0, SEEK_END);
    long int curPos = ftell(file);
    fseek(file, pos, 0);

    return (curPos - pos);
}

void decode(FILE* input, FILE* output) {
    fseek(input, 1, SEEK_CUR);
    if (isEmptyFile(input) == 0)
        return;

    size_t lengthOfMessage = readLengthOfMessage(input);

    unsigned char buff[16]; // buffer for reading
    size_t lengthBuff = fread(buff, 1, 16, input);

    size_t bufPos = 0; // MAX == 15
    size_t k = 0;

    Tree* newHuffmanTree = buildTree(input, buff, &k, &bufPos, &lengthBuff);
    size_t countOfSymbols = 0;
    while (countOfSymbols < lengthOfMessage)
        decodeData(input, output, newHuffmanTree, buff, &k, &bufPos, &lengthBuff, &countOfSymbols);

    clearTree(newHuffmanTree);
}

