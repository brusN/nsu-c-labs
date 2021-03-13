#ifndef LAB8_0_LAB8_0_SOURCE_H
#define LAB8_0_LAB8_0_SOURCE_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define STATUS_SUCCESS 0
#define STATUS_BAD_NUMBER_VERTICES 1
#define STATUS_BAD_NUMBER_EDGES 2
#define STATUS_BAD_VERTEX 3
#define STATUS_BAD_NUMBER_LINES 4
#define STATUS_BAD_LENGTH 5
#define STATUS_NO_SPANNING_TREE 6
#define ERROR_OF_READING 7

typedef struct st_edges Edge;
struct st_edges {
    int from;
    int to;
    int length;
};

void printErr(char status);
void checkRightInput(int countVertex, int countEdges);

void readNewValue(char *type, void* elem);
void checkRightInputValues(int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge, int countVertex);
void fillElem(Edge *edge, int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge);
void fillQueue(Edge *edges, int countVertex, int countEdges);
void quickSort(Edge *array, int point1, int point2);  // sorting by key == length

int findParent(int *parentArr, int i);
void swapInt(int* x, int* y);
int kruskalAlg(Edge* edges, Edge* spanningTree, int countVertex, int countEdges);
void printSpanningTreeEdges(Edge* spanningTree, int countVertex);

#endif //LAB8_0_LAB8_0_SOURCE_H

