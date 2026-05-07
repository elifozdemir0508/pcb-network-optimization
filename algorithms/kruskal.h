#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <stdbool.h>

#include "../core/graph.h"

typedef struct {
    int totalWeight;
    int edgeCount;
    bool isSpanning;
    Edge edges[MAX_NODES - 1];
} MSTResult;

MSTResult kruskal_mst(const Graph *graph);

#endif
