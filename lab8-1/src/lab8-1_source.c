#include "lab8-1_source.h"

void printErr(char status) {
    switch(status) {
        case STATUS_BAD_NUMBER_VERTICES:
            printf("bad number of vertices");
            break;
        case STATUS_BAD_NUMBER_EDGES:
            printf("bad number of edges");
            break;
        case STATUS_BAD_VERTEX:
            printf("bad vertex");
            break;
        case STATUS_BAD_NUMBER_LINES:
            printf("bad number of lines");
            break;
        case STATUS_BAD_LENGTH:
            printf("bad length");
            break;
        case STATUS_NO_SPANNING_TREE:
            printf("no spanning tree");
            break;
        default:
            printf("Program has been terminated!\n");
            break;
    }
    exit(0);
}

void checkRightInput(int countVertex, int countEdges) {
    if (countVertex < 0 || countVertex > 5000)
        printErr(STATUS_BAD_NUMBER_VERTICES);

    if (countEdges < 0 || countEdges >  countVertex * (countVertex + 1) / 2)
        printErr(STATUS_BAD_NUMBER_EDGES);
}

void checkRightInputValues(int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge, int countVertex) {
    if ((fromVertexNewEdge < 1 || fromVertexNewEdge > countVertex) || (toVertexNewEdge < 1 || toVertexNewEdge > countVertex))
        printErr(STATUS_BAD_VERTEX);

    if (lengthNewEdge < 0)
        printErr(STATUS_BAD_LENGTH);
}

pQueue *initPriorityQueue(int maxSize) {
    pQueue *newPQ = (pQueue *)malloc(sizeof(pQueue));
    newPQ->edgesHeap = (Edge *) malloc(sizeof(Edge) * (maxSize + 1));
    newPQ->curSize = 0;
    newPQ->maxSize = maxSize;
    return newPQ;
}

short* initParentArr(int countVertex) {
    short* parentArr = (short*)malloc(sizeof(short) * countVertex);
    for (int i = 0; i < countVertex; ++i)
        parentArr[i] = NO_CHILD;

    return parentArr;
}

int** initAdjMatrix(int countVertex) {
    int** newMatrix = (int**)malloc(sizeof(int*) * countVertex);
    for (int i = 0; i < countVertex; ++i) {
        newMatrix[i] = (int *) malloc(sizeof(int) * countVertex);
        for (int j = 0; j < countVertex; ++j)
            newMatrix[i][j] = -1;
    }

    return newMatrix;
}

void fillAdjMatrix(int** matrix, int countVertex, int countEdges) {
    int fromVertex;
    int toVertex;
    int weight;

    for (int i = 0; i < countEdges; ++i) {
        if (scanf("%d %d %d", &fromVertex, &toVertex, &weight) != 3)
            printErr(STATUS_BAD_NUMBER_LINES);
        checkRightInputValues(fromVertex, toVertex, weight, countVertex);

        matrix[fromVertex-1][toVertex-1] = weight;
        matrix[toVertex-1][fromVertex-1] = weight;
    }
}

void addNewEdgeInPQ(pQueue * PQ, short * indexVertexInHeap, int numVertex, int weight) {
    Edge newEdge;
    newEdge.numVertex = numVertex;
    newEdge.weight = weight;

    indexVertexInHeap[numVertex] = (short) PQ->curSize++;
    PQ->edgesHeap[indexVertexInHeap[numVertex]] = newEdge;
}

void swapEdges(Edge* e1, Edge* e2) {
    Edge box = *e1;
    *e1 = *e2;
    *e2 = box;
}

void heapify(pQueue * PQ,  short * indexEdgeInHeap, int index, int maxSize) {
    int indexRoot = index;
    int indexLeftChild = index * 2 + 1;
    int indexRightChild = index * 2 + 2;

    Edge rootNode = PQ->edgesHeap[indexRoot];
    int constRootVertex = rootNode.numVertex;

    if(indexLeftChild < maxSize) {
        Edge lcNode = *(PQ->edgesHeap + indexLeftChild);
        if(lcNode.weight < rootNode.weight){
            indexRoot = indexLeftChild;
            rootNode = *(PQ->edgesHeap+ indexRoot);
            indexEdgeInHeap[lcNode.numVertex] = (short)index;
            indexEdgeInHeap[constRootVertex] = (short)indexRoot;
        }
    }

    if(indexRightChild < maxSize) {
        Edge rcNode = *(PQ->edgesHeap+ indexRightChild);
        if(rcNode.weight < rootNode.weight){
            indexRoot = indexRightChild;
            indexEdgeInHeap[rcNode.numVertex] = (short)index;
            indexEdgeInHeap[rootNode.numVertex] = (short)indexRoot;
        }
    }

    if(indexRoot != index){
        swapEdges(&PQ->edgesHeap[index], &PQ->edgesHeap[indexRoot]);
        heapify(PQ, indexEdgeInHeap, indexRoot, PQ->curSize);
    }
}

void increaseNode(pQueue * PQ, short * indexVertexInHeap, short i) {
    while( (i+1)/2 > 0 && PQ->edgesHeap[(i+1)/2-1].weight > PQ->edgesHeap[i].weight) { // if parent weight > son's weigth
        indexVertexInHeap[PQ->edgesHeap[(i+1)/2-1].numVertex] = i; // update index in array of index in heap
        indexVertexInHeap[PQ->edgesHeap[i].numVertex] = (short)((i+1)/2-1); // update too

        swapEdges( &(PQ->edgesHeap[(i+1)/2-1]), &(PQ->edgesHeap[i])); // swap nodes
        i = (i + 1) / 2 - 1;
    }
}

void enqueue(pQueue * PQ, short * indexVertexInHeap, int numVertex, int weight) {
    if (PQ->maxSize > PQ->curSize) {
        addNewEdgeInPQ(PQ, indexVertexInHeap, numVertex, weight);
        increaseNode(PQ, indexVertexInHeap,(short)(PQ->curSize - 1));
    }
}

Edge dequeue(pQueue * PQ,  short * indexVertexInHeap) {
    Edge minEdge = PQ->edgesHeap[0]; // save root values
    PQ->edgesHeap[0] = PQ->edgesHeap[PQ->curSize - 1]; // delete this FUCKIN "--" !!!!!!!!! (i found the bug finally c:)
    --(PQ->curSize);
    indexVertexInHeap[minEdge.numVertex] = -1;
    heapify(PQ, indexVertexInHeap, 0, PQ->curSize);
    return minEdge;
}

void findMST(int ** graphAdjMatrix, pQueue * PQ, short *parent, int countVertex) {
    char *isVisitedVertex = (char*)malloc(sizeof(char) * countVertex + 1); // set of vertex
    short *indexVertexInHeap = (short*)malloc(sizeof(short) * (countVertex + 1)); // index of vertex in PQ

    for (int i = 0; i < countVertex; ++i) {
        isVisitedVertex[i] = UNVISITED_VERTEX;
        indexVertexInHeap[i] = -1;
    }

    // first step algorithm
    isVisitedVertex[0] = VISITED_VERTEX;
    indexVertexInHeap[0] = 0;
    for (int i = 0; i < countVertex; i++) {
        if (graphAdjMatrix[0][i] != -1 && i != 0) {
            enqueue(PQ, indexVertexInHeap, i, graphAdjMatrix[0][i]);
            parent[i] = 0;
        }
    }

    // second step algorithm
    while (PQ->curSize > 0) {
        Edge curEdge = dequeue(PQ, indexVertexInHeap);
        for (int i = 0; i < countVertex; i++) {
            if (graphAdjMatrix[curEdge.numVertex][i] != -1 && i != curEdge.numVertex && isVisitedVertex[i] == UNVISITED_VERTEX) {
                if (indexVertexInHeap[i] == NOT_IN_HEAP) {
                    enqueue(PQ, indexVertexInHeap, i, (int) graphAdjMatrix[curEdge.numVertex][i]);
                    parent[i] = (short)curEdge.numVertex;
                } else {
                    int w = PQ->edgesHeap[indexVertexInHeap[i]].weight;
                    if (w > graphAdjMatrix[curEdge.numVertex][i]) {
                        PQ->edgesHeap[indexVertexInHeap[i]].weight = (int) graphAdjMatrix[curEdge.numVertex][i];
                        increaseNode(PQ, indexVertexInHeap, indexVertexInHeap[i]);
                        parent[i] = (short)curEdge.numVertex;
                    }
                }
            }
        }
        isVisitedVertex[curEdge.numVertex] = VISITED_VERTEX;
    }

    free(isVisitedVertex);
    free(indexVertexInHeap);
}

void printMST(short* parentArr, int countVertex) {
    for (int i = 1; i < countVertex; ++i)
          printf("%d %d\n", (int)parentArr[i] + 1, i + 1);
}

void freeMemoryAdjMatrix(int** matrix, int countVertex) {
    for (int i = 0; i < countVertex; ++i)
        free(matrix[i]);
    free(matrix);
}

void freeMemoryPQ(pQueue * PQ) {
    free(PQ->edgesHeap);
    free(PQ);
}


