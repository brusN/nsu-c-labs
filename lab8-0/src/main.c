#include "lab8-0_source.h"

int main(void) {

    int countVertex, countEdges;
    readNewValue("%d", &countVertex);
    readNewValue("%d", &countEdges);
    checkRightInput(countVertex, countEdges);

    Edge *edges = (Edge*)malloc(sizeof(Edge) * countEdges);
    fillQueue(edges, countVertex, countEdges); // read and check values of edges
    quickSort(edges, 0, (int)countEdges - 1); // sorting by key == length

    Edge *spanningTree = (Edge*)malloc(sizeof(Edge) * countVertex);

    if (kruskalAlg(edges, spanningTree, countVertex, countEdges) == countVertex)  // kruskal alg func returns counts of added edges
        printSpanningTreeEdges(spanningTree, countVertex);
    else
        printErr(STATUS_NO_SPANNING_TREE);

    free(edges);
    free(spanningTree);

    return 0;
}

