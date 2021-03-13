#include "lab7_header.h"
// 
void freeMemory(Graph* graphVertex, int countVertex) {
    for (int i = 0; i < countVertex; ++i)
        free(graphVertex[i].edges);
    free(graphVertex);
}

void printErr(char status, FILE *output) {
    switch(status) {
        case STATUS_BAD_NUMBER_VERTICES:
           fprintf(output, "bad number of vertices");
            break;
        case STATUS_BAD_NUMBER_EDGES:
            fprintf(output, "bad number of edges");
            break;
        case STATUS_BAD_VERTEX:
            fprintf(output, "bad vertex");
            break;
        case STATUS_BAD_NUMBER_LINES:
            fprintf(output, "bad number of lines");
            break;
        case STATUS_IMPOSSIBLE_SORT:
            fprintf(output, "impossible to sort");
            break;
        default:
            fprintf(output, "error of reading!");
            break;
    }
    exit(0);
}

void checkBadInput(int countVertex, int countEdges, FILE* output) {
    if(countVertex == -1 || countEdges == -1) {
        printErr(STATUS_BAD_NUMBER_LINES, output);
    }
    if  (countVertex < 0 || countVertex > 1000)
        printErr(STATUS_BAD_NUMBER_VERTICES, output);

    if (countEdges < 0 || countEdges > countVertex * (countVertex - 1) / 2)
        printErr(STATUS_BAD_NUMBER_EDGES, output);
}

void resetGraph(Graph* graphVertex, int countVertex) {
    for (int i = 0; i < countVertex; ++i) {
        graphVertex[i].color = WHITE_VERTEX;
        graphVertex[i].size = 0;
        graphVertex[i].edges = NULL;
    }
}

void addNewEdge(Graph* vertex, int numberAnotherVertex) {
    ++vertex->size;
    vertex->edges = realloc(vertex->edges, sizeof(int) * vertex->size);
    vertex->edges[vertex->size - 1] = numberAnotherVertex;
}

void fillGraph(Graph * vertex, int countVertex, int countEdges, FILE* input, FILE* output) {
    int fromEdge, toEgde;
    for (int i = 0; i < countEdges; ++i) {
        if (fscanf(input, "%d %d", &fromEdge, &toEgde) != 2)
            printErr(STATUS_BAD_NUMBER_LINES, output);

        if ((fromEdge < 0 || fromEdge > countVertex) || (toEgde < 0 || toEgde > countVertex))
            printErr(STATUS_BAD_VERTEX, output);

        addNewEdge(&vertex[fromEdge - 1], toEgde);
    }
}

void graphDepthTravese(Graph * graph, int countVertex, int numVertex, int *stack, int *stackPos, FILE* output) {
    if (graph[numVertex-1].color == BLACK_VERTEX)
        return;

    if (graph[numVertex-1].color == GRAY_VERTEX) {
        freeMemory(graph, countVertex);
        printErr(STATUS_IMPOSSIBLE_SORT, output);
    }

    graph[numVertex-1].color = GRAY_VERTEX;

    for (int i = 0; i < graph[numVertex - 1].size; ++i)
        graphDepthTravese(graph, countVertex, graph[numVertex-1].edges[i], stack, stackPos, output);

    stack[*stackPos] = numVertex;
    ++*stackPos;

    graph[numVertex-1].color = BLACK_VERTEX;
}

void graphTopologicSort(Graph* graphVertex, int countVertex, FILE* output) {
    int stack[(const int)countVertex];
    int stackPos = 0;

    for (int i = 0; i < countVertex; ++i)
       graphDepthTravese(graphVertex, countVertex, i + 1, stack, &stackPos, output);

    for (int i = stackPos - 1; i >= 0; i--)
        fprintf(output, "%d ", stack[i]);

    for (int i = 0; i < countVertex; i++) {
        if (graphVertex[i].color == WHITE_VERTEX)
            fprintf(output, "%d ", i + 1);
    }
}

