#include <stdio.h>
#include "graph.h"

void initGraph(Graph *graph, int nodeCount) {
    graph->nodeCount = nodeCount;
    graph->edgeCount = 0;

    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph *graph, int source, int target, int weight) {
    if (source < 0 || source >= graph->nodeCount ||
        target < 0 || target >= graph->nodeCount) {
        printf("Invalid node index.\n");
        return;
        }

    graph->adjacencyMatrix[source][target] = weight;
    graph->adjacencyMatrix[target][source] = weight;

    if (graph->edgeCount < MAX_EDGES) {
        graph->edges[graph->edgeCount].source = source;
        graph->edges[graph->edgeCount].target = target;
        graph->edges[graph->edgeCount].weight = weight;
        graph->edgeCount++;
    } else {
        printf("Maximum edge limit reached.\n");
    }
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

void printEdges(Graph *graph) {
    printf("Edges:\n");

    for (int i = 0; i < graph->edgeCount; i++) {
        printf("%d -- %d  weight: %d\n",
               graph->edges[i].source,
               graph->edges[i].target,
               graph->edges[i].weight);
    }
}