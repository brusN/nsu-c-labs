#ifndef LAB9_LAB9_SOURCE_H
#define LAB9_LAB9_SOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STATUS_BAD_NUMBER_VERTICES 1
#define STATUS_BAD_NUMBER_EDGES 2
#define STATUS_BAD_VERTEX 3
#define STATUS_BAD_NUMBER_LINES 4
#define STATUS_BAD_LENGTH 5

#define NOT_FOUND -1
#define NO_CHILD -1
#define VISITED 1
#define NOT_VISITED 0
#define OVERFLOW 1
#define NOT_OVERFLOW 0

void printErr(char status);
void checkRightInput(int countVertex, int countEdges, int startV, int finishV);
void checkRightInputValues(int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge, int countVertex);

short* initParentArr(int countVertex);
unsigned int* initPathLengthArr(int countVertex);
char* initOverflowArr(int countVertex);
unsigned int** initAdjMatrix(int countVertex);
void fillAdjMatrix(unsigned int** matrix, int countVertex, int countEdges);
int findMinWeightIndex(unsigned int *pathLength, char *isVisitedVertex, int startV, int countVertex);
void dijkstraAlg(unsigned int** matrix, unsigned int* pathLength, short* parent, char* isOverflow, int startV, int countVertex);

void printPath(short *parent, int lastPoint);
void printPathsToAll(unsigned int* pathLength, char* isOverflow, int countVertex);
void printMostShortPath(int startV, int finishV, int countEdges, short* parentArr, char* isOverflow);

void freeMatrix(unsigned int** matrix, int countVertex);

#endif //LAB9_LAB9_SOURCE_H

