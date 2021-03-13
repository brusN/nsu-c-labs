#include "lab9_source.h"

int main() {
    int countVertex, startV, finishV, countEdges;
    if (scanf("%d %d %d %d", &countVertex, &startV, &finishV, &countEdges) != 4)
        printErr(STATUS_BAD_NUMBER_LINES);
    checkRightInput(countVertex, countEdges, startV, finishV);

    unsigned int **matrix = initAdjMatrix(countVertex); // fill adjMatrix with reading edges
    fillAdjMatrix(matrix, countVertex, countEdges);

    short *parentArr = initParentArr(countVertex);
    unsigned int *pathLength = initPathLengthArr(countVertex);
    char *isOverflow = initOverflowArr(countVertex);
    dijkstraAlg(matrix, pathLength, parentArr, isOverflow, startV - 1, countVertex);

    printPathsToAll(pathLength, isOverflow, countVertex); // print path length from startV to all
    printMostShortPath(startV, finishV, countEdges, parentArr, isOverflow);

    freeMatrix(matrix, countVertex);
    free(parentArr);
    free(pathLength);
    free(isOverflow);

    return 0;
}

