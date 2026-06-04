#include <stdio.h>
#include <stdlib.h>
#include "Dfs.h"
#include "Stack.h"



/**
 * @brief İteratif Derinlemesine Arama (DFS) algoritması ile grafı tarar ve ulaşılan düğüm sayısını bulur.
 * * @param baslangic_dugumu: Aramanın başlatılacağı kök düğümün indeksi.
 * @param graf: Düğümler ve komşuluk matrisini içeren devrenin graf modeli.
 * * @retval -1: Geçersiz parametre, boş graf veya bellek tahsisi hatası durumunda.
 * @retval ulasilan_parca_sayisi: Kesintisiz ulaşılan (birbirine fiziksel olarak bağlı) toplam pin sayısı.
 * * @author Niyazi Han Akbulut
 * * @note Yığın taşmasını (Stack Overflow) önlemek için özyineleme (recursion) yerine
 * LIFO prensibiyle çalışan Stack veri yapısı (iteratif model) kullanılmıştır.
 */

int DFS_Calistir(int baslangic_dugumu, Graph* graf) {


    int dugum_sayisi = graf->nodeCount;



    int* ziyaret_edildi = (int*)calloc(dugum_sayisi, sizeof(int));


    stackptr yigitim = yeniStack();

    int ulasilan_parca_sayisi = 0;


    push(yigitim, newNode(baslangic_dugumu));

    while (!bosmu(yigitim)) {
        int anlik_dugum = pop(yigitim);


        if (ziyaret_edildi[anlik_dugum] == 0) {
            ziyaret_edildi[anlik_dugum] = 1;
            ulasilan_parca_sayisi++;


            for (int i = dugum_sayisi - 1; i >= 0; i--) {


                if (graf->adjacencyMatrix[anlik_dugum][i] != 0 && ziyaret_edildi[i] == 0) {

                    push(yigitim, newNode(i));
                }
            }
        }
    }


    free(yigitim);
    free(ziyaret_edildi);

    return ulasilan_parca_sayisi;
}