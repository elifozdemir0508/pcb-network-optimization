#include <stdio.h>
#include "graph.h"
#include "Connectedness.h"

int main() {
    printf("--- CONNECTEDNESS (BAGLANTILILIK) TESTI BASLIYOR ---\n\n");

    // ==========================================
    // TEST 1: SAGLAM (TAM BAGLI) DEVRE
    // ==========================================
    printf("TEST 1: Tam Bagli Devre Testi\n");
    Graph saglam_graf;
    initGraph(&saglam_graf, 4); // 4 parcali bir devre

    // Parcalari birbirine bagliyoruz (0-1-2-3 seklinde bir zincir)
    addEdge(&saglam_graf, 0, 1, 5);
    addEdge(&saglam_graf, 1, 2, 3);
    addEdge(&saglam_graf, 2, 3, 7);

    // Muduru cagirip kontrol ettiriyoruz
    int sonuc1 = CheckConnectedness(&saglam_graf);
    if (sonuc1 == 1) {
        printf("Test 1 Basarili: Sistem devrenin saglam oldugunu dogru tespit etti.\n\n");
    } else {
        printf("Test 1 Basarisiz: Sistem saglam devreye kopuk dedi!\n\n");
    }


    // ==========================================
    // TEST 2: KOPUK (HATALI) DEVRE
    // ==========================================
    printf("TEST 2: Kopuk Devre Testi\n");
    Graph kopuk_graf;
    initGraph(&kopuk_graf, 5); // 5 parcali bir devre

    // Sadece 0, 1 ve 2'yi bagliyoruz.
    // 3 ve 4 numarali parcalara hic kablo cekmiyoruz (Havada kalacaklar)
    addEdge(&kopuk_graf, 0, 1, 4);
    addEdge(&kopuk_graf, 1, 2, 2);

    // Muduru cagirip kontrol ettiriyoruz
    int sonuc2 = CheckConnectedness(&kopuk_graf);
    if (sonuc2 == 0) {
        printf("Test 2 Basarili: Sistem devredeki kopuklugu basariyla yakaladi!\n");
    } else {
        printf("Test 2 Basarisiz: Sistem kopuk devreyi saglam zannetti!\n");
    }

    printf("\n--- TESTLER TAMAMLANDI ---\n");

    return 0;
}