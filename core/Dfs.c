#include <stdio.h>
#include <stdlib.h>
#include "Dfs.h"
#include "Stack.h"

int DFS_Calistir(int baslangic_dugumu, int** graf, int dugum_sayisi) {
    int* ziyaret_edildi = (int*)calloc(dugum_sayisi, sizeof(int));

    printf("\n--- Iteratif DFS Taramasi Basliyor (Baslangic: %d) ---\n", baslangic_dugumu);
    printf("Ziyaret Sirasi (Parca Numaralari): ");


    stackptr yigitim = yeniStack();
    int ulasilan_parca_sayisi = 0;

    //Baslangic dugumunu Stack'e ekle
    push(yigitim, newNode(baslangic_dugumu));

    // 3. Stack bosalana kadar devam et
    while (!bosmu(yigitim)) {

        //  En ustteki elemani al
        int anlik_dugum = pop(yigitim);

        //  Eger bu parcaya daha once GIDILMEDIyse islem yap
        if (ziyaret_edildi[anlik_dugum] == 0) {

            // Parcayi ziyaret ettik, ekrana yaz ve isaretle
            printf("%d ", anlik_dugum);
            ziyaret_edildi[anlik_dugum] = 1;
            ulasilan_parca_sayisi++;

            // Komsularini bul ve Stack'e at.
            for (int i = dugum_sayisi - 1; i >= 0; i--) {


                if (graf[anlik_dugum][i] == 1 && ziyaret_edildi[i] == 0) {

                    push(yigitim, newNode(i));
                }
            }
        }
    }

    // 7. Bellek temizligi
    free(yigitim);
    free(ziyaret_edildi);
    printf("\n\n--- DFS Taramasi Bitti ---\n");
    return ulasilan_parca_sayisi;
}