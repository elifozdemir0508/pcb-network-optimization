#include <stdio.h>
#include "Dfs.h"
#include "graph.h" // Yeni statik yapiyi cagiriyoruz

int main() {
    // 1. Yeni statik Graph paketi (nesnesi) olusturuluyor
    Graph benim_grafim;

    // 2. Grafi 5 parcali olacak sekilde baslatiyoruz (Senin kendi initGraph fonksiyonun)
    initGraph(&benim_grafim, 5);

    // 3. Kablolari (Kenarlari) bagliyoruz.
    // DFS icin agirligin ne oldugu onemli degil (0 olmasin yeter), bu yuzden rastgele agirliklar (1) verdik.
    // Eski testteki o meşhur PCB devremizin ayni baglantilari:
    addEdge(&benim_grafim, 0, 1, 1);
    addEdge(&benim_grafim, 0, 2, 1);
    addEdge(&benim_grafim, 1, 3, 1);
    addEdge(&benim_grafim, 2, 4, 1);
    addEdge(&benim_grafim, 3, 4, 1);

    /* NOT: Senin Graph.c icindeki addEdge fonksiyonun eger cift yonlu (undirected) ekleme yapiyorsa,
       yani 0'dan 1'e eklerken ayni zamanda 1'den 0'a da ekliyorsa yukaridaki 5 satir yeterlidir.
       Eger tek yonluyse, terslerini de (ornegin addEdge(&benim_grafim, 1, 0, 1); seklinde) eklemelisin. */

    // 4. Testi Baslat
    printf("PCB Devresi DFS (Derinlik) Testi - Yeni Mimarisi Ile\n");

    // Artik uzun uzun parametreler yok! Sadece baslangic noktasi ve paketin adresi:
    int ulasilanlar = DFS_Calistir(0, &benim_grafim);

    printf("\nDFS Islemi Bitti. Toplam Ulasilan Parca Sayisi: %d\n", ulasilanlar);

    return 0;
}

