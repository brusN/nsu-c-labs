#include "lab8-0_source.h"

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

void readNewValue(char *type, void* elem) {
    if (scanf(type, elem) == 0)
        printErr(STATUS_BAD_NUMBER_LINES);
}

void checkRightInputValues(int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge, int countVertex) {
    if ((fromVertexNewEdge < 1 || fromVertexNewEdge > countVertex) || (toVertexNewEdge < 1 || toVertexNewEdge > countVertex))
        printErr(STATUS_BAD_VERTEX);

    if (lengthNewEdge < 0)
        printErr(STATUS_BAD_LENGTH);
}

void fillElem(Edge *elem, int fromVertexNewEdge, int toVertexNewEdge, int lengthNewEdge) {
    elem->from = fromVertexNewEdge;
    elem->to = toVertexNewEdge;
    elem->length = lengthNewEdge;
}

void fillQueue(Edge *edges, int countVertex, int countEdges) {
    int fromVertexNewEdge; // for reading and filling queue
    int toVertexNewEdge; //
    int lengthNewEdge; //

    for (int i = 0; i < countEdges; ++i) {
       if (scanf("%d %d %d", &fromVertexNewEdge, &toVertexNewEdge, &lengthNewEdge) != 3)
           printErr(STATUS_BAD_NUMBER_LINES);

        checkRightInputValues(fromVertexNewEdge, toVertexNewEdge, lengthNewEdge, countVertex);
        fillElem(&edges[i], fromVertexNewEdge, toVertexNewEdge, lengthNewEdge);
    }
}

void quickSort(Edge *array, int point1, int point2) { // sorting by key == length
    if (point1 < point2) {
        int i = point1;
        int j = point2;
        int pivot = array[(i + j) / 2].length;
        do {
            while (array[i].length < pivot)
                ++i;
            while (array[j].length > pivot)
                --j;

            if (i <= j) {
                Edge box = array[i];
                array[i] = array[j];
                array[j] = box;
                ++i;
                --j;
            }
        } while (i <= j);

        if (j > 0)
            quickSort(array, point1, j);

        if (i < point2)
            quickSort(array, i, point2); // pls don't kill me :c
    }
}

int findParent(int *parentArr, int i) { // find func with removed recursion
    while (i != parentArr[i])
        i = parentArr[i];

    return parentArr[i];
}

void swapInt(int* x, int* y) { // simple swap
    int box = *x;
    *x = *y;
    *y = box;
}

int kruskalAlg(Edge* edges, Edge* spanningTree, int countVertex, int countEdges) { // returns counts of visited vertexs
    int countVisitedVertex = 0;
    int curPos = 0;

    int parentArr[(const int)countVertex + 1];
    int rankArr[(const int)countVertex + 1];
    for (int i = 0; i < countVertex + 1; i++) {
        parentArr[i] = i;
        rankArr[i] = 0;
    }

    for (int i = 0; i < countEdges; ++i) { // Using Union-find with path compression and rank heuristics
        int x = findParent(parentArr, edges[i].from);
        int y = findParent(parentArr, edges[i].to);
        if (x != y) {
            if (rankArr[x] < rankArr[y])
                swapInt(&x, &y);
            parentArr[y] = x;
            if (rankArr[x] == rankArr[y])
                ++rankArr[x];

            spanningTree[curPos++] = edges[i]; // add edge in final tree
            ++countVisitedVertex;
        }
    }

    return countVisitedVertex + 1;
}
//
void printSpanningTreeEdges(Edge* spanningTree, int countVertex) {
    for (int i = 0; i < countVertex - 1; ++i)
        printf("%d %d\n", spanningTree[i].from, spanningTree[i].to);
}

