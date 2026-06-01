#include <stdio.h>
#include <stdlib.h>
#include "Dfs.h"
#include "Stack.h"

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