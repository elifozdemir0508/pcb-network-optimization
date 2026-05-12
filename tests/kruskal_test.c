#include <stdbool.h>
#include <stdio.h>

#include "../core/graph.h"
#include "../algorithms/kruskal.h"

static bool assert_equal_int(const char *label, int expected, int actual) {
    if (expected != actual) {
        printf("[FAIL] %s: expected=%d actual=%d\n", label, expected, actual);
        return false;
    }

    printf("[PASS] %s\n", label);
    return true;
}

static bool assert_equal_bool(const char *label, bool expected, bool actual) {
    if (expected != actual) {
        printf("[FAIL] %s: expected=%s actual=%s\n",
               label,
               expected ? "true" : "false",
               actual ? "true" : "false");
        return false;
    }

    printf("[PASS] %s\n", label);
    return true;
}

static bool test_connected_graph(void) {
    Graph graph;
    initGraph(&graph, 4);

    addEdge(&graph, 0, 1, 4);
    addEdge(&graph, 0, 2, 2);
    addEdge(&graph, 1, 3, 5);
    addEdge(&graph, 2, 3, 1);
    addEdge(&graph, 1, 2, 3);

    MSTResult result = kruskal_mst(&graph);

    bool ok = true;
    ok &= assert_equal_int("connected.edgeCount", 3, result.edgeCount);
    ok &= assert_equal_int("connected.totalWeight", 6, result.totalWeight);
    ok &= assert_equal_bool("connected.isSpanning", true, result.isSpanning);
    return ok;
}

static bool test_disconnected_graph(void) {
    Graph graph;
    initGraph(&graph, 4);

    addEdge(&graph, 0, 1, 1);
    addEdge(&graph, 2, 3, 1);

    MSTResult result = kruskal_mst(&graph);

    bool ok = true;
    ok &= assert_equal_int("disconnected.edgeCount", 2, result.edgeCount);
    ok &= assert_equal_int("disconnected.totalWeight", 2, result.totalWeight);
    ok &= assert_equal_bool("disconnected.isSpanning", false, result.isSpanning);
    return ok;
}

int main(void) {
    bool ok = true;

    ok &= test_connected_graph();
    ok &= test_disconnected_graph();

    if (!ok) {
        printf("Kruskal tests failed.\n");
        return 1;
    }

    printf("Kruskal tests passed.\n");
    return 0;
}
