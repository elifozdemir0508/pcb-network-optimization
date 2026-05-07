#include <stdio.h>
#include "../core/graph.h"

int main() {
    Graph graph;

    initGraph(&graph, 4);

    addEdge(&graph, 0, 1, 4);
    addEdge(&graph, 0, 2, 2);
    addEdge(&graph, 1, 3, 5);
    addEdge(&graph, 2, 3, 1);

    printAdjacencyMatrix(&graph);
    printEdges(&graph);

    return 0;
}
