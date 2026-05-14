#include "kruskal.h"

#include <stdlib.h>

#include "../core/union_find.h"

static int compare_edges_by_weight(const void *a, const void *b) {
    const Edge *edge_a = (const Edge *)a;
    const Edge *edge_b = (const Edge *)b;

    if (edge_a->weight < edge_b->weight) {
        return -1;
    }
    if (edge_a->weight > edge_b->weight) {
        return 1;
    }
    return 0;
}

MSTResult kruskal_mst(const Graph *graph) {
    MSTResult result = {0};

    if (!graph || graph->nodeCount <= 0 || graph->nodeCount > MAX_NODES) {
        return result;
    }

    if (graph->edgeCount <= 0) {
        return result;
    }

    Edge sorted_edges[MAX_EDGES];
    int edge_count = graph->edgeCount;

    for (int i = 0; i < edge_count; ++i) {
        sorted_edges[i] = graph->edges[i];
    }

    qsort(sorted_edges, edge_count, sizeof(Edge), compare_edges_by_weight);

    UnionFind *uf = union_find_create((uint32_t)graph->nodeCount);
    if (!uf) {
        return result;
    }

    for (int i = 0; i < edge_count; ++i) {
        const Edge *edge = &sorted_edges[i];

        if (union_find_union(uf, (uint32_t)edge->source, (uint32_t)edge->target)) {
            result.edges[result.edgeCount] = *edge;
            result.edgeCount += 1;
            result.totalWeight += edge->weight;

            if (result.edgeCount == graph->nodeCount - 1) {
                break;
            }
        }
    }

    result.isSpanning = (result.edgeCount == graph->nodeCount - 1);

    union_find_destroy(uf);
    return result;
}
