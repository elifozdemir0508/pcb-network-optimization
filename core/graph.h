#ifndef GRAPH_H
#define GRAPH_H

#define MAX_NODES 100
#define MAX_EDGES (MAX_NODES * MAX_NODES)

typedef struct {
    int source;
    int target;
    int weight;
} Edge;

typedef struct {
    int nodeCount;
    int edgeCount;
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    Edge edges[MAX_EDGES];
} Graph;

void initGraph(Graph *graph, int nodeCount);
void addEdge(Graph *graph, int source, int target, int weight);
void printAdjacencyMatrix(Graph *graph);
void printEdges(Graph *graph);

#endif
