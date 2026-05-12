#include <stdio.h>
#include "connectedness.h"
#include "Dfs.h" //Dfs kullanır

int CheckConnectedness(int** graf, int dugum_sayisi) {

    //  DFS'yi 0 numarali parcadan baslat ve ulastigi parca sayisini ogren
    int ulasilan_parca_sayisi = DFS_Calistir(0, graf, dugum_sayisi);

    // Eger DFS devredeki tüm parcalara ulasabildiyse
    if (ulasilan_parca_sayisi == dugum_sayisi) {
        printf("[CONNECTEDNESS] Devre durumu: MUKEMMEL. (%d/%d parcaya ulasildi)\n", ulasilan_parca_sayisi, dugum_sayisi);
        return 1; // 1 = True (Baglantili)
    }

    else {
        printf("[CONNECTEDNESS] Devre durumu: HATA! KOPUK. Sadece %d parcaya ulasildi, %d parca eksik.\n",
                ulasilan_parca_sayisi, (dugum_sayisi - ulasilan_parca_sayisi));
        return 0; // Kopuk
    }
}