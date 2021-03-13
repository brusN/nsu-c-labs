#include <stdio.h>
#include "lab7_header.h"
// 
int main(void) {

    FILE *input, *output;
    input = fopen("in.txt", "r");
    output = fopen("out.txt", "w");

    if (input == NULL)
        exit(1);

    if (output == NULL)
        exit(1);

    int countVertex, countEdges;

    if (fscanf(input, "%d", &(countVertex)) == -1)  // read countVertex
        printErr(STATUS_BAD_NUMBER_LINES, output);

    if (fscanf(input, "%d", &(countEdges)) == -1) // read countEdges
        printErr(STATUS_BAD_NUMBER_LINES, output);

    checkBadInput(countVertex, countEdges, output);
    
    Graph *graph = (Graph *)malloc(sizeof(Graph) * countVertex); //
    resetGraph(graph, countVertex);
    fillGraph(graph, countVertex, countEdges, input, output);

    graphTopologicSort(graph, countVertex, output);

    freeMemory(graph, countVertex); // free graph memory
    fclose(input);
    fclose(output);

    return 0;
}

