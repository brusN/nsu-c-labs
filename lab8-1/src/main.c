#include "lab8-1_source.h"

int main(void) {
    int countVertex, countEdges;
    if (scanf("%d %d", &countVertex, &countEdges) != 2)
        printErr(STATUS_BAD_NUMBER_LINES);
        
    if (countVertex == 0 && countEdges == 0)
        printErr(STATUS_NO_SPANNING_TREE);
    checkRightInput(countVertex, countEdges);

    int** matrix = initAdjMatrix(countVertex); // fill adjMatrix with reading edges
    fillAdjMatrix(matrix, countVertex, countEdges);

    short* parent = initParentArr(countVertex); // main block
    pQueue * heapEdges = initPriorityQueue(countVertex);
    findMST(matrix, heapEdges, parent, countVertex); // Prim's alg

    for (int i = 1; i < countVertex; ++i)
        if (parent[i] == NO_CHILD)
            printErr(STATUS_NO_SPANNING_TREE);
    printMST(parent, countVertex);

    free(parent);
    freeMemoryPQ(heapEdges);
    freeMemoryAdjMatrix(matrix, countVertex);
    return 0;
}


