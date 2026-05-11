#include <stdio.h>
#include <stdlib.h>
#include "Dfs.h" // Sadece menuyu cagiriyoruz

int main() {
    int dugum_sayisi = 5;

    // Dinamik matris olusturma
    int** graf = (int**)malloc(dugum_sayisi * sizeof(int*));
    for(int i = 0; i < dugum_sayisi; i++) {
        graf[i] = (int*)malloc(dugum_sayisi * sizeof(int));
    }

    // BFS testindeki ayni PCB devre baglantilari
    // [0] Guc Kaynagi, [1] Direnc, [2] Kapasitor, [3] Cip, [4] LED
    int gecici_graf[5][5] = {
        {0, 1, 1, 0, 0}, // 0'dan -> 1 ve 2'ye
        {1, 0, 0, 1, 0}, // 1'den -> 0 ve 3'e
        {1, 0, 0, 0, 1}, // 2'den -> 0 ve 4'e
        {0, 1, 0, 0, 1}, // 3'ten -> 1 ve 4'e
        {0, 0, 1, 1, 0}  // 4'ten -> 2 ve 3'e
    };

    // Matrisi dinamik yapiya kopyala
    for(int i = 0; i < dugum_sayisi; i++) {
        for(int j = 0; j < dugum_sayisi; j++) {
            graf[i][j] = gecici_graf[i][j];
        }
    }

    //  Testi Baslat
    printf("PCB Devresi DFS (Derinlik) Testi\n");
    DFS_Calistir(0, graf, dugum_sayisi); // Aramaya 0 numaradan basla

    //  Temizlik
    for(int i = 0; i < dugum_sayisi; i++) {
        free(graf[i]);
    }
    free(graf);

    return 0;
}