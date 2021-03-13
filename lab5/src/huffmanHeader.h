#ifndef LABB5_HUFFMANHEADER_H
#define LABB5_HUFFMANHEADER_H

#define BUFF_SIZE 256
#define TABLE_SIZE 256
#define NOT_FOUND 256
#define BYTE_SIZE 8

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct st_freqTable FreqTable;
struct st_freqTable {
    unsigned char symbol;
    size_t freq;
};

typedef struct st_Tree Tree;
struct st_Tree {
    Tree* link[2];
    FreqTable value;
};

typedef struct st_listFreq listFreq;
struct st_listFreq {
    listFreq* next;
    Tree* leaf; // заменить на Node
};

typedef struct st_codeTable codeTable;
struct st_codeTable {
    size_t length;
    unsigned char* code;
};

void clearList(listFreq* root);
void clearTree(Tree* root);
void printError();
FILE* openFile(const char *filePath, const char *mode);
void closeFiles(FILE* file1, FILE* file2);

void resetTable(FreqTable *table);
void fillFreqTable(FreqTable freqTable[], size_t *totalLength, FILE* input);
void stableSortFreqTable(FreqTable* freqTable);
size_t findFirstNonZeroFreq(FreqTable* table);
Tree* initNewTree(FreqTable elem);

listFreq* initNewElemListFreq(FreqTable value);
void addElemListFreq(listFreq** root, listFreq* elem);
listFreq* createListFreq(listFreq *root, FreqTable *table, int index);

Tree* removeTopList(listFreq **top);
Tree* createNewNode(listFreq* list);
listFreq* insertNewElemList(listFreq* list);
Tree* createHuffmanTree(listFreq* rootList);
void resetCodeTable (codeTable * table);

void findCode(Tree* huffmanTree, codeTable tableCode[TABLE_SIZE], unsigned char code[TABLE_SIZE], size_t level);
void fillCodeTable(Tree* huffmanTree, codeTable* codeTable);

void writeLengthOfMessage(int *length, FILE* output);
// static int getBit(unsigned char byte);
void write1Bite(unsigned char* byte, size_t *k, unsigned char bite, FILE* output);
void encodeTree(Tree* huffmanTree, unsigned char* byte, size_t *k, size_t *levelMax, size_t *level, FILE* output);
void encodeData(Tree* huffmanTree, codeTable *table, FILE* input, FILE* output);
void clearTableOfCodes(codeTable* table);
void encode(FILE* input, FILE* output);

size_t readLengthOfMessage(FILE* input);
void doShift( FILE* input, unsigned char* buff, size_t* k, size_t* bufPos, size_t* lengthBuff);
void fillLeaf(Tree* leaf, unsigned char symbol);
Tree* buildTree(FILE *input, unsigned char* buff, size_t *k, size_t *bufPos, size_t *lengthBuff);
void decodeData(FILE *input, FILE* output, Tree* newHuffmanTree, unsigned char* buff, size_t *k, size_t *bufPos, size_t *lengthBuff, size_t *countOfSymbol);
long int isEmptyFile(FILE* file);
void decode(FILE* input, FILE* output);
#endif //LABB5_HUFFMANHEADER_H

