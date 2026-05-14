#include "io_adapter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Minimal, permissive helpers for parsing numbers from JSON-like input.
static const char *skip_whitespace(const char *s) {
    while (s && *s && isspace((unsigned char)*s)) ++s;
    return s;
}

// Find an object member by name (very permissive, not a full JSON parser).
// Returns pointer to the first char after the ':' or NULL.
static const char *find_member(const char *json, const char *name) {
    const char *p = json;
    size_t name_len = strlen(name);
    while ((p = strstr(p, "\""))) {
        if (strncmp(p+1, name, name_len) == 0 && p[1+name_len] == '"') {
            const char *colon = strchr(p + 1 + name_len, ':');
            if (colon) return colon + 1;
        }
        p += 1;
    }
    return NULL;
}

// Parse an integer from a char pointer (skips whitespace)
static int parse_int(const char **pp) {
    const char *p = skip_whitespace(*pp);
    int sign = 1;
    if (*p == '-') { sign = -1; ++p; }
    int val = 0;
    while (isdigit((unsigned char)*p)) { val = val*10 + (*p - '0'); ++p; }
    *pp = p;
    return val * sign;
}

// Parse a double from a char pointer (skips whitespace)
static double parse_double(const char **pp) {
    const char *p = skip_whitespace(*pp);
    char *endptr = NULL;
    double v = strtod(p, &endptr);
    if (endptr == p) {
        *pp = p;
        return 0.0;
    }
    *pp = endptr;
    return v;
}

// Very small helper to parse the 'nodes' array and count nodes.
static int count_array_items(const char *arr_start) {
    int count = 0;
    const char *p = arr_start;
    while (p && *p) {
        if (*p == '{') {
            ++count;
            p = strchr(p, '}');
            if (!p) break;
            ++p;
        } else {
            ++p;
        }
    }
    return count;
}

int json_to_graph(const char *json_str, Graph *out_graph) {
    if (!json_str || !out_graph) return -1;
    memset(out_graph, 0, sizeof(*out_graph));

    // Try to get node_count from request_meta.node_count first
    const char *p = find_member(json_str, "request_meta");
    int nodeCount = 0;
    if (p) {
        const char *pc = strstr(p, "node_count");
        if (pc) {
            const char *valp = strchr(pc, ':');
            if (valp) {
                ++valp;
                nodeCount = parse_int(&valp);
            }
        }
    }

    // If not found, count explicit nodes array
    const char *nodes_p = find_member(json_str, "nodes");
    if (!nodeCount && nodes_p) {
        const char *arr = strchr(nodes_p, '[');
        if (arr) nodeCount = count_array_items(arr);
    }

    if (nodeCount <= 0 || nodeCount > MAX_NODES) return -2;
    initGraph(out_graph, nodeCount);

    // Parse edges array
    const char *edges_p = find_member(json_str, "edges");
    if (!edges_p) return 0; // no edges is acceptable

    const char *arr = strchr(edges_p, '[');
    if (!arr) return -3;
    const char *cur = arr;
    while ((cur = strchr(cur, '{')) != NULL) {
        const char *end = strchr(cur, '}');
        if (!end) break;
        // Within this object, find source, target, weight
        const char *obj = cur;
        const char *srcm = strstr(obj, "\"source\"");
        const char *tarm = strstr(obj, "\"target\"");
        const char *wtm = strstr(obj, "\"weight\"");
        if (!srcm || !tarm || !wtm) { cur = end+1; continue; }

        const char *valp;
        int source=0, target=0;
        double weightd=0.0;

        valp = strchr(srcm, ':'); if (valp) { ++valp; source = parse_int(&valp); }
        valp = strchr(tarm, ':'); if (valp) { ++valp; target = parse_int(&valp); }
        valp = strchr(wtm, ':'); if (valp) { ++valp; weightd = parse_double(&valp); }

        int weight = (int)lround(weightd);
        if (source < 0 || source >= out_graph->nodeCount) { cur = end+1; continue; }
        if (target < 0 || target >= out_graph->nodeCount) { cur = end+1; continue; }

        addEdge(out_graph, source, target, weight);

        cur = end + 1;
    }

    return 0;
}

char *graph_to_json(const Graph *graph) {
    if (!graph) return NULL;
    // Roughly estimate required size
    size_t bufsize = 1024 + (size_t)graph->edgeCount * 64;
    char *buf = malloc(bufsize);
    if (!buf) return NULL;
    char *p = buf;
    int written = snprintf(p, bufsize, "{\"node_count\": %d, \"edges\": [", graph->nodeCount);
    p += written; bufsize -= written;

    for (int i = 0; i < graph->edgeCount; ++i) {
        const Edge *e = &graph->edges[i];
        // weight as float with 2 decimal places (original code uses ints, so print .00)
        written = snprintf(p, bufsize, "%s{\"source\": %d, \"target\": %d, \"weight\": %.2f}",
                           (i==0?"":" , "), e->source, e->target, (double)e->weight);
        p += written; bufsize -= written;
        if (bufsize < 64) {
            // expand
            size_t used = p - buf;
            bufsize += 1024;
            char *nb = realloc(buf, used + bufsize);
            if (!nb) { free(buf); return NULL; }
            p = nb + used;
            buf = nb;
        }
    }

    snprintf(p, bufsize, "]}\n");
    return buf;
}

char *mstresult_to_json(const MSTResult *res) {
    if (!res) return NULL;
    size_t bufsize = 512 + (size_t)res->edgeCount * 64;
    char *buf = malloc(bufsize);
    if (!buf) return NULL;
    char *p = buf;
    int written = snprintf(p, bufsize, "{\"response_meta\": {\"total_cost\": %d}, \"mst_edges\": [", res->totalWeight);
    p += written; bufsize -= written;

    for (int i = 0; i < res->edgeCount; ++i) {
        const Edge *e = &res->edges[i];
        written = snprintf(p, bufsize, "%s{\"source\": %d, \"target\": %d}", (i==0?"":" , "), e->source, e->target);
        p += written; bufsize -= written;
        if (bufsize < 64) {
            size_t used = p - buf;
            bufsize += 1024;
            char *nb = realloc(buf, used + bufsize);
            if (!nb) { free(buf); return NULL; }
            p = nb + used;
            buf = nb;
        }
    }

    snprintf(p, bufsize, "]}\n");
    return buf;
}
