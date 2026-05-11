#include <stdio.h>
#include <stdlib.h>
#include "Queue.h" //  kuyruk yapısı


void BFS_Calistir(int baslangic_dugumu, int** graf, int dugum_sayisi) {

    // 1. Ziyaret edilenler listesi (Kopukluk veya sonsuz donguyu onlemek icin)
    int* ziyaret_edildi = (int*)calloc(dugum_sayisi, sizeof(int));

    printf("\n--- BFS Taramasi Basliyor (Baslangic: %d) ---\n", baslangic_dugumu);
    printf("Ziyaret Sirasi: ");

    //  Yeni bir kuyruk olustur
    kuyrukptr kuyrugum = newQueue();

    //  Baslangic dugumunu kuyruga ekle ve "ziyaret edildi" olarak isaretle
    enqueue(kuyrugum, baslangic_dugumu);
    ziyaret_edildi[baslangic_dugumu] = 1;

    // 4. Kuyruk bosalana kadar dalgalar halinde ilerle
    while (!isEmpty(kuyrugum)) {

        // Kuyrugun en basindaki elemani al
        int anlik_dugum = dequeue(kuyrugum);

        // Cikan elemani ekrana yaz
        printf("%d ", anlik_dugum);

        // Bu elemanin butun komsularina bakılır
        for (int i = 0; i < dugum_sayisi; i++) {

            // EGER bu iki parca arasinda kablo (baglanti) varsa (graf[...][i] == 1)
            // VE bu parcaya daha once hic gitmediysek (ziyaret_edildi[i] == 0)
            if (graf[anlik_dugum][i] == 1 && ziyaret_edildi[i] == 0) {

                enqueue(kuyrugum, i);     // Listeye ekle ki sira ona da gelsin
                ziyaret_edildi[i] = 1;    // Isaretle ki baska bir yoldan tekrar gelmeyelim
            }
        }
    }

    //  Temizlik
    freeQueue(kuyrugum);
    free(ziyaret_edildi);

    printf("\n--- BFS Taramasi Bitti ---\n");
}