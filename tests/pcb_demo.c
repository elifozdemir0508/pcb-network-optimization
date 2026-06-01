#include <stdbool.h>
#include <stdio.h>

#include "../algorithms/kruskal.h"
#include "../core/Connectedness.h"
#include "../core/graph.h"

static void print_separator(const char *title) {
    printf("\n==========================================\n");
    printf("  %s\n", title);
    printf("==========================================\n");
}

static void build_example_graph(Graph *graph) {
    initGraph(graph, 5);

    addEdge(graph, 0, 1, 320);
    addEdge(graph, 0, 2, 403);
    addEdge(graph, 0, 3, 316);
    addEdge(graph, 1, 3, 180);
    addEdge(graph, 1, 4, 223);
    addEdge(graph, 2, 4, 452);
    addEdge(graph, 3, 4, 269);
}

static void print_mst_result(const MSTResult *result) {
    printf("Secilen MST kenarlari (%d adet):\n", result->edgeCount);
    for (int i = 0; i < result->edgeCount; ++i) {
        printf("  %d -- %d   agirlik: %d\n",
               result->edges[i].source,
               result->edges[i].target,
               result->edges[i].weight);
    }
    printf("\nToplam baglanti maliyeti: %d\n", result->totalWeight);
    printf("Spanning Tree olusturuldu: %s\n",
           result->isSpanning ? "EVET" : "HAYIR");
}

static void build_mst_subgraph(Graph *mst_graph, const MSTResult *result,
                                int node_count) {
    initGraph(mst_graph, node_count);
    for (int i = 0; i < result->edgeCount; ++i) {
        addEdge(mst_graph,
                result->edges[i].source,
                result->edges[i].target,
                result->edges[i].weight);
    }
}

int main(void) {
    print_separator("PCB BAGLANTI AGI OPTIMIZASYONU - DEMO");

    printf("\n[ADIM 1] Ornek devre grafi olusturuluyor...\n");
    printf("  Dugum sayisi: 5 (PCB bilesenleri)\n");
    printf("  Kenar sayisi: 7 (olasi baglantilar)\n");

    Graph input_graph;
    build_example_graph(&input_graph);

    print_separator("ADIM 2: BASLANGIC GRAFI");
    printAdjacencyMatrix(&input_graph);
    printf("\n");
    printEdges(&input_graph);

    print_separator("ADIM 3: KRUSKAL ONCESI BAGLANTI KONTROLU");
    int connected_before = CheckConnectedness(&input_graph);
    if (!connected_before) {
        printf("\n[HATA] Baslangic grafi kopuk. MST hesaplanamaz.\n");
        return 1;
    }

    print_separator("ADIM 4: KRUSKAL ALGORITMASI CALISTIRILIYOR");
    MSTResult result = kruskal_mst(&input_graph);
    print_mst_result(&result);

    print_separator("ADIM 5: MST SONRASI BAGLANTI DOGRULAMASI");
    Graph mst_graph;
    build_mst_subgraph(&mst_graph, &result, input_graph.nodeCount);
    printAdjacencyMatrix(&mst_graph);
    printf("\n");
    int connected_after = CheckConnectedness(&mst_graph);

    print_separator("OZET / DOGRULAMA");
    const int expected_edge_count = input_graph.nodeCount - 1;
    const int expected_total = 1122;

    printf("Beklenen kenar sayisi : %d   Gercek: %d   [%s]\n",
           expected_edge_count, result.edgeCount,
           (result.edgeCount == expected_edge_count) ? "OK" : "FAIL");
    printf("Beklenen toplam maliyet: %d  Gercek: %d  [%s]\n",
           expected_total, result.totalWeight,
           (result.totalWeight == expected_total) ? "OK" : "FAIL");
    printf("Spanning bayragi      : %s\n", result.isSpanning ? "true" : "false");
    printf("MST sonrasi bagli     : %s\n", connected_after ? "EVET" : "HAYIR");

    const bool ok = (result.edgeCount == expected_edge_count) &&
                    (result.totalWeight == expected_total) &&
                    result.isSpanning && connected_after;

    if (ok) {
        printf("\n[SONUC] Demo basarili. Algoritma dogru calisiyor.\n");
        return 0;
    }
    printf("\n[SONUC] Demo basarisiz. Beklenenler ile cikti uyusmuyor.\n");
    return 1;
}
