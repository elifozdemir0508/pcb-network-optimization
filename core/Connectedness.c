#include <stdio.h>
#include "connectedness.h"
#include "Dfs.h" //Dfs kullanır

int CheckConnectedness(Graph *graph) {

    //  DFS'yi 0 numarali parcadan baslat ve ulastigi parca sayisini ogren
    int ulasilan_parca_sayisi = DFS_Calistir(0, graph);

    // Eger DFS devredeki tüm parcalara ulasabildiyse
    if (ulasilan_parca_sayisi == graph->nodeCount) {
        printf("[CONNECTEDNESS] Devre durumu: MUKEMMEL. (%d/%d parcaya ulasildi)\n",ulasilan_parca_sayisi, graph->nodeCount);
        return 1; // Baglantili
    }

    else {
        printf("[CONNECTEDNESS] Devre durumu: HATA! KOPUK. Sadece %d parcaya ulasildi, %d parca eksik.\n",
                ulasilan_parca_sayisi, (graph->nodeCount - ulasilan_parca_sayisi));
        return 0; // Kopuk
    }
}