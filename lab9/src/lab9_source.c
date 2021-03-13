#include "lab9_source.h"
//
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
        default:
            printf("Program has been terminated!\n");
            break;
    }
    exit(0);
}

void checkRightInput(int countVertex, int countEdges, int startV, int finishV) {
    if (countVertex < 0 || countVertex > 5000)
        printErr(STATUS_BAD_NUMBER_VERTICES);

    if (countEdges < 0 || countEdges >  countVertex * (countVertex + 1) / 2)
        printErr(STATUS_BAD_NUMBER_EDGES);

    if (startV < 1 || startV > countVertex || finishV < 1 || finishV > countVertex) {
        printErr(STATUS_BAD_VERTEX);
    }
}

void checkRightInputValues(int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge, int countVertex) {
    if ((fromVertexNewEdge < 1 || fromVertexNewEdge > countVertex) || (toVertexNewEdge < 1 || toVertexNewEdge > countVertex))
        printErr(STATUS_BAD_VERTEX);

    if (lengthNewEdge < 0)
        printErr(STATUS_BAD_LENGTH);
}

short* initParentArr(int countVertex) {
    short* parentArr = (short*)malloc(sizeof(short) * countVertex);
    for (int i = 0; i < countVertex; ++i)
        parentArr[i] = NO_CHILD;

    return parentArr;
}

unsigned int* initPathLengthArr(int countVertex) {
    unsigned int* newArr = (unsigned int*)malloc(sizeof(unsigned int) * countVertex);
    for (int i = 0; i < countVertex; ++i)
        newArr[i] = UINT_MAX;
    return newArr;
}

char* initOverflowArr(int countVertex) {
    char* newArr = (char*)malloc(countVertex);
    for (int i = 0; i < countVertex; ++i)
        newArr[i] = NOT_OVERFLOW;

    return newArr;
}


unsigned int** initAdjMatrix(int countVertex) {
    unsigned int** newMatrix = (unsigned int**)malloc(sizeof(unsigned int*) * countVertex);
    for (int i = 0; i < countVertex; ++i) {
        newMatrix[i] = (unsigned int *) malloc(sizeof(int) * countVertex);
        for (int j = 0; j < countVertex; ++j)
            newMatrix[i][j] = UINT_MAX;
    }

    return newMatrix;
}

void fillAdjMatrix(unsigned int** matrix, int countVertex, int countEdges) {
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

int findMinWeightIndex(unsigned int *pathLength, char *isVisitedVertex, int startV, int countVertex) {
    long long minimalWeight = LLONG_MAX;
    int minimalWeightIndex = -1;
    for(int i = 0; i < countVertex; ++i) {
        if (i != startV && isVisitedVertex[i] == NOT_VISITED && pathLength[i] < minimalWeight) {
            minimalWeight = pathLength[i];
            minimalWeightIndex = i;
        }
    }
    return minimalWeightIndex;
}

void dijkstraAlg(unsigned int** matrix, unsigned int* pathLength, short* parent, char* isOverflow, int startV, int countVertex) {
    pathLength[startV] = 0;
    char *isVisitedVertex = (char *) malloc(countVertex);
    for (int i = 0; i < countVertex; ++i)
        isVisitedVertex[i] = NOT_VISITED;
    isVisitedVertex[startV] = VISITED;

    int minWeightIndex = 0;
    long long int minimalWeight = LLONG_MAX;

    // Первый этап
    for (int i = 0; i < countVertex; i++) {
        if (i != startV && matrix[startV][i] != UINT_MAX) {
            pathLength[i] = matrix[startV][i];
            parent[i] = (short) startV;
            if (minimalWeight > matrix[startV][i]) {
                minimalWeight = matrix[startV][i];
                minWeightIndex = i;
            }
        }
    }

    int countVisitedVertex = 1;

    // Второй этап
    while (countVisitedVertex < countVertex && minWeightIndex != NOT_FOUND) {
        for (int i = 0; i < countVertex; ++i) {
            if (i != minWeightIndex && i != startV && matrix[minWeightIndex][i] != UINT_MAX) {
                long long int sum = (long long int) pathLength[minWeightIndex] + (long long int) matrix[minWeightIndex][i];
                if (pathLength[i] > sum) {
                    if (sum > INT_MAX) {
                        pathLength[i] = UINT_MAX;
                        isOverflow[i] = OVERFLOW;
                    } else
                        pathLength[i] = (unsigned int) sum;
                    parent[i] = (short) minWeightIndex;
                }
            }
        }
        isVisitedVertex[minWeightIndex] = VISITED;
        minWeightIndex = findMinWeightIndex(pathLength, isVisitedVertex, startV, countVertex);
        ++countVisitedVertex;
    }
	
	free(isVisitedVertex);
}

void printPathsToAll(unsigned int* pathLength, char* isOverflow, int countVertex) {
    for (int i = 0; i < countVertex; ++i) {
        if (pathLength[i] == UINT_MAX && isOverflow[i] == NOT_OVERFLOW) {
            printf("oo ");
        } else if (isOverflow[i] == OVERFLOW) {
            printf("INT_MAX+ ");
        } else {
            printf("%u ", pathLength[i]);
        }
    }
    printf("\n");
}

void printPath(short *parent, int lastPoint) {
    while (lastPoint != -1) {
        int point = parent[lastPoint];
        if (point == NO_CHILD)
            return;
        printf("%d ", point + 1);
        lastPoint = point;
    }
}

void printMostShortPath(int startV, int finishV, int countEdges, short* parentArr, char* isOverflow) {
    if (startV == finishV) {
        printf("%d", startV);
    } else if (parentArr[finishV - 1] == NO_CHILD) {
        printf("no path");
    } else if (isOverflow[finishV - 1] == OVERFLOW && countEdges != 2) {
        printf("overflow");
    } else {
        printf("%d ", finishV);
        printPath(parentArr, finishV - 1);
    }
}

void freeMatrix(unsigned int** matrix, int countVertex) {
    for (int i = 0; i < countVertex; ++i)
        free(matrix[i]);
    free(matrix);
}

