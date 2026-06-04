#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"


/**
 * @brief Kuyruğa eklenecek yeni bir düğüm (node) oluşturur ve bellekte yer ayırır.
 * * @param veri: Düğümün içinde tutulacak tam sayı değeri (Pin ID vb.).
 * * @retval NULL: Bellek tahsisi başarısız olursa (Memory Overflow).
 * @retval node: İlk değerleri atanmış düğüm işaretçisi.
 * * @author Niyazi Han Akbulut
 * * @note Sadece modül içinden çağrılacağı için 'static' olarak tanımlanmıştır. O(1) karmaşıklığındadır.
 */

static nodeptr newNode(int veri){
    nodeptr node = (nodeptr)malloc(sizeof(Node));
    node->data=veri;
    node->next=NULL;
    return node;
}


/**
 * @brief Dinamik bağlantılı liste tabanlı kuyruk (Queue) yapısını bellekte oluşturur.
 * * @retval NULL: Bellekten yer ayrılamaması durumunda döndürülür.
 * @retval k: İlk değerleri (bas ve son işaretçileri NULL) atanmış kuyruk adresi.
 * * @author Niyazi Han Akbulut
 * * @note Yapısal doğası gereği O(1) zaman karmaşıklığına sahiptir.
 */

kuyrukptr newQueue(){
    kuyrukptr k=(kuyrukptr)malloc(sizeof(Kuyruk));
    k->bas=NULL;
    k->son=NULL;
    return k;
}



/**
 * @brief Kuyruğun sonuna (rear) yeni bir eleman ekler (FIFO prensibi).
 * * @param k: İşlem yapılacak kuyruk yapısının işaretçisi.
 * @param veri: Eklenecek düğümün verisi.
 * * @author Niyazi Han Akbulut
 * * @note O(1) zaman karmaşıklığı ile çalışır.
 */

void  enqueue(kuyrukptr k, int veri){
    nodeptr node = newNode(veri);
    if(k->bas==NULL)
        k->bas= node;
    else
        k->son->next=node;
    k->son= node;
   }


/**
 * @brief Kuyruğun boş olup olmadığını kontrol eder.
 * * @param k: Kontrol edilecek kuyruk işaretçisi.
 * * @retval 1 (true): Kuyruk boşsa veya geçersizse.
 * @retval 0 (false): Kuyrukta eleman varsa.
 * * @author Niyazi Han Akbulut
 */

int isEmpty(kuyrukptr k){
    return (k->bas == NULL);
}



/**
 * @brief Kuyruğun başındaki (front) elemanı çıkarır, verisini döndürür ve belleğini temizler.
 * * @param k: İşlem yapılacak kuyruk yapısının işaretçisi.
 * * @retval -1: Kuyruk boşsa veya geçersiz parametre girildiyse.
 * @retval cikan_veri: Kuyruktan çıkarılan düğümün verisi.
 * * @author Niyazi Han Akbulut
 * * @note O(1) zaman karmaşıklığı. free() fonksiyonu ile memory leak (bellek sızıntısı) engellenmiştir.
 */

int dequeue(kuyrukptr k) {
    if(isEmpty(k)) {
        printf("Hata!:Kuyruk boş\n");
        return -1;
    }
    nodeptr temp = k->bas;
    int cikan_veri = temp->data;

    k->bas = k->bas->next;
    if(k->bas == NULL) {
        k->son = NULL;
    }
    free(temp);
    return cikan_veri;
}



      /**
       * @brief Kuyruğu ve içindeki tüm düğümleri bellekten güvenli bir şekilde siler.
       * * @param k: Serbest bırakılacak kuyruk işaretçisi.
       * * @author Niyazi Han Akbulut
     */

    void freeQueue(kuyrukptr k) {
        while (!isEmpty(k)) {
            dequeue(k);
        }
        free(k);
    }


/**
 * @brief Kuyruktaki mevcut eleman sayısını hesaplar.
 * * @param k: İşlem yapılacak kuyruk işaretçisi.
 * * @retval sayac: Kuyruktaki toplam eleman sayısı.
 * * @author Niyazi Han Akbulut
 * * @note Tüm listeyi gezdiği için O(N) zaman karmaşıklığına sahiptir.
 */

    int size(kuyrukptr k){
        nodeptr temp=k->bas;
        int sayac=0;
        while(temp){
            sayac++;
            temp=temp->next;
        }
        return sayac;
    }


/**
 * @brief Kuyruğun içeriğini terminale yazdırır (Hata ayıklama / Debugging için).
 * * @param k: Yazdırılacak kuyruk işaretçisi.
 * * @author Niyazi Han Akbulut
 */

    void show(kuyrukptr k){
        nodeptr temp = k->bas;
        while(temp){
            printf("%d --> ", temp->data);
            temp=temp->next;
        }
    printf("\n");
    }



