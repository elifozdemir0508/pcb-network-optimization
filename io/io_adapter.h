#ifndef IO_ADAPTER_H
#define IO_ADAPTER_H

#include <stddef.h>
#include "../core/graph.h"
#include "../algorithms/kruskal.h"

// Parse a JSON string (as described in todo.md) into a Graph struct.
// Returns 0 on success, non-zero on parse/validation error.
int json_to_graph(const char *json_str, Graph *out_graph);

// Serialize a Graph into a JSON string. The returned string is heap-allocated
// and must be freed by the caller using free(). Returns NULL on error.
char *graph_to_json(const Graph *graph);

// Serialize an MSTResult into JSON. Returned string must be freed by caller.
char *mstresult_to_json(const MSTResult *res);

#endif
