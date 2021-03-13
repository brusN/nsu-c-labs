#ifndef LAB8_1_LAB8_1_SOURCE_H
#define LAB8_1_LAB8_1_SOURCE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STATUS_SUCCESS 0
#define STATUS_BAD_NUMBER_VERTICES 1
#define STATUS_BAD_NUMBER_EDGES 2
#define STATUS_BAD_VERTEX 3
#define STATUS_BAD_NUMBER_LINES 4
#define STATUS_BAD_LENGTH 5
#define STATUS_NO_SPANNING_TREE 6
#define ERROR_OF_READING 7

#define INFINITY 2147483647
#define UNVISITED_VERTEX 0
#define VISITED_VERTEX 1
#define NOT_IN_HEAP -1
#define NO_CHILD -1

typedef struct st_Edge Edge;
struct st_Edge {
    int numVertex;
    int weight;
};

typedef struct st_pQueue pQueue;
struct st_pQueue {
    int maxSize;
    int curSize;
    Edge* edgesHeap;
};

void printErr(char status);
void checkRightInput(int countVertex, int countEdges);
void checkRightInputValues(int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge, int countVertex);

pQueue *initPriorityQueue(int maxSize);
short* initParentArr(int countVertex);
int** initAdjMatrix(int countVertex);
void fillAdjMatrix(int** matrix, int countVertex, int countEdges);

void addNewEdgeInPQ(pQueue * PQ, short * indexVertexInHeap, int numVertex, int weight);
void swapEdges(Edge* e1, Edge* e2);
void heapify(pQueue * PQ,  short * indexEdgeInHeap, int index, int maxSize);
void increaseNode(pQueue * PQ, short * indexVertexInHeap, short i);
void enqueue(pQueue * PQ, short * indexVertexInHeap, int numVertex, int weight);
Edge dequeue(pQueue * PQ,  short * indexVertexInHeap);
void findMST(int ** graphAdjMatrix, pQueue * PQ, short *parent, int countVertex);
void printMST(short* parentArr, int countVertex);

void freeMemoryPQ(pQueue * PQ);
void freeMemoryAdjMatrix(int** matrix, int countVertex);

#endif //LAB8_1_LAB8_1_SOURCE_H

