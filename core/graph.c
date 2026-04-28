#include <stdio.h>

#define MAX_NODES 100

typedef struct {
    int source;
    int target;
    int weight;
} Edge;

typedef struct {
    int nodeCount;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
} Graph;

void initGraph(Graph *graph, int nodeCount) {
    graph->nodeCount = nodeCount;

    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph *graph, int source, int target, int weight) {
    if (source < 0 || source >= graph->nodeCount || target < 0 || target >= graph->nodeCount) {
        printf("Invalid node index.\n");
        return;
    }

    graph->adjacencyMatrix[source][target] = weight;
    graph->adjacencyMatrix[target][source] = weight;
}

void printAdjacencyMatrix(Graph *graph) {
    printf("Adjacency Matrix:\n");

    for (int i = 0; i < graph->nodeCount; i++) {
        for (int j = 0; j < graph->nodeCount; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Graph graph;

    initGraph(&graph, 4);

    addEdge(&graph, 0, 1, 4);
    addEdge(&graph, 0, 2, 2);
    addEdge(&graph, 1, 3, 5);
    addEdge(&graph, 2, 3, 1);

    printAdjacencyMatrix(&graph);

    return 0;
}
