#ifndef LAB7_LAB7_HEADER_H
#define LAB7_LAB7_HEADER_H
//
/* Vertex color */
#define WHITE_VERTEX  0 //  is non checked
#define GRAY_VERTEX 1 // has been checked one time
#define BLACK_VERTEX 2 // has been pushed into stack

/* Status possible errors */
#define STATUS_SUCCESS 0
#define STATUS_BAD_NUMBER_VERTICES 1
#define STATUS_BAD_NUMBER_EDGES 2
#define STATUS_BAD_VERTEX 3
#define STATUS_BAD_NUMBER_LINES 4
#define STATUS_IMPOSSIBLE_SORT 5
#define ERROR_OF_READING 6

#include <stdio.h>
#include <stdlib.h>

typedef struct st_graphVertex Graph;
struct st_graphVertex {
    int* edges;
    int size; // кол-во вершин, в которые можно попасть
    char color;
};

void freeMemory(Graph* graphVertex, int countVertex);
void printErr(char status, FILE* output);

void checkBadInput(int countVertex, int countEdges, FILE* output);

void resetGraph(Graph* graphVertex, int countVertex);
void addNewEdge(Graph *vertex, int numberAnotherVertex);
void fillGraph(Graph * graph, int countVertex, int countEdges, FILE* input, FILE* output);

void graphDepthTravese(Graph * graph, int countVertex, int numVertex, int *stack, int *stackPos, FILE* output);
void graphTopologicSort(Graph* graphVertex, int countVertex, FILE* output);

#endif //LAB7_LAB7_HEADER_H

