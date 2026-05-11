#include <stdio.h>
#include <stdlib.h>
#include "Bfs.h"

int main() {
    int dugum_sayisi = 5;

    int** graf = (int**)malloc(dugum_sayisi * sizeof(int*));
    for(int i = 0; i < dugum_sayisi; i++) {
        graf[i] = (int*)malloc(dugum_sayisi * sizeof(int));
    }

    int gecici_graf[5][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };

    for(int i = 0; i < dugum_sayisi; i++) {
        for(int j = 0; j < dugum_sayisi; j++) {
            graf[i][j] = gecici_graf[i][j];
        }
    }

    // Fonksiyon Bfs.c icinden calisacak
    printf("PCB Devresi BFS (Dalga) Testi\n");
    BFS_Calistir(0, graf, dugum_sayisi);

    for(int i = 0; i < dugum_sayisi; i++) {
        free(graf[i]);
    }
    free(graf);

    return 0;
}