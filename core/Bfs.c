#include <stdio.h>
#include <stdlib.h>
#include "Queue.h" //  kuyruk yapısı


/**
 * @brief Graf üzerinde Sığlamasına Arama (BFS) işlemini gerçekleştirir.
 * * @param graf: Düğümler arası bağlantıları tutan Komşuluk Matrisi (Adjacency Matrix).
 * @param dugum_sayisi: Sistemdeki toplam düğüm (pin) sayısı.
 * @param baslangic_dugumu: Aramanın başlatılacağı kök düğümün indeksi.
 * * @retval false: Geçersiz parametre veya bellek tahsisi hatası durumunda işlemi güvenle iptal eder.
 * @retval true: BFS taraması başarıyla tamamlandığında döndürülür.
 * * @author Niyazi Han Akbulut
 * * @note Zaman karmaşıklığı Komşuluk Matrisi kullanıldığı için O(V^2)'dir.
 * Kuyruk (Queue) mimarisi kullanılarak en kısa yol tespiti için katman katman (level-order) ilerler.
 */

void BFS_Calistir(int baslangic_dugumu, int** graf, int dugum_sayisi) {


    int* ziyaret_edildi = (int*)calloc(dugum_sayisi, sizeof(int));

    printf("\n--- BFS Taramasi Basliyor (Baslangic: %d) ---\n", baslangic_dugumu);
    printf("Ziyaret Sirasi: ");


    kuyrukptr kuyrugum = newQueue();


    enqueue(kuyrugum, baslangic_dugumu);
    ziyaret_edildi[baslangic_dugumu] = 1;


    while (!isEmpty(kuyrugum)) {


        int anlik_dugum = dequeue(kuyrugum);


        printf("%d ", anlik_dugum);


        for (int i = 0; i < dugum_sayisi; i++) {


            if (graf[anlik_dugum][i] == 1 && ziyaret_edildi[i] == 0) {

                enqueue(kuyrugum, i);
                ziyaret_edildi[i] = 1;
            }
        }
    }


    freeQueue(kuyrugum);
    free(ziyaret_edildi);

    printf("\n--- BFS Taramasi Bitti ---\n");
}