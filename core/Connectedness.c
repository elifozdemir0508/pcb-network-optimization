#include <stdio.h>
#include "Connectedness.h"
#include "Dfs.h"


/**
 * @brief Devrenin topolojik olarak tam bağlantılı (connected) olup olmadığını test eder.
 * * @param graph: Analiz edilecek devrenin graf işaretçisi (pointer).
 * * @retval 0 (false): Geçersiz parametre, DFS hatası veya devrede izole/kopuk pinler varsa.
 * @retval 1 (true): Devre tam bağlantılıysa (Tüm pinlere eksiksiz ulaşıldıysa).
 * * @author Niyazi Han Akbulut
 * * @note Kruskal gibi Minimum Kapsayan Ağaç (MST) algoritmalarından önce
 */

int CheckConnectedness(Graph *graph) {


    int ulasilan_parca_sayisi = DFS_Calistir(0, graph);


    if (ulasilan_parca_sayisi == graph->nodeCount) {
        printf("[CONNECTEDNESS] Devre durumu: MUKEMMEL. (%d/%d parcaya ulasildi)\n",ulasilan_parca_sayisi, graph->nodeCount);
        return 1;
    }

    else {
        printf("[CONNECTEDNESS] Devre durumu: HATA! KOPUK. Sadece %d parcaya ulasildi, %d parca eksik.\n",
                ulasilan_parca_sayisi, (graph->nodeCount - ulasilan_parca_sayisi));
        return 0;
    }
}