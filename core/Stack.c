#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * @brief Stack'e eklenecek yeni bir düğüm (node) oluşturur ve bellekte yer ayırır.
 * * @param data: Düğümün içinde tutulacak tam sayı değeri (Pin ID vb.).
 * * @retval NULL: Bellek tahsisi başarısız olursa (Memory Overflow).
 * @retval n: İlk değerleri atanmış düğüm işaretçisi.
 * * @author Niyazi Han Akbulut
 */

Nodeptr newNode(int data) {
    Nodeptr n = (Nodeptr)malloc(sizeof(Node));
    if (n != NULL) {
        n->data = data;
        n->forward = NULL;
    }
    return n;
}


/**
 * @brief Dinamik bağlantılı liste tabanlı yığın (Stack) yapısını bellekte oluşturur.
 * * @retval NULL: Bellekten yer ayrılamaması durumunda döndürülür.
 * @retval s1: İlk değerleri (bas işaretçisi NULL) atanmış yığın adresi.
 * * @author Niyazi Han Akbulut
 */

stackptr yeniStack(void) {
    stackptr s1 = (stackptr)malloc(sizeof(stack));
    if (s1 != NULL) {
        s1->bas = NULL;
    }
    return s1;
}


/**
 * @brief Yığındaki mevcut eleman sayısını hesaplar.
 * * @param stack: İşlem yapılacak yığın işaretçisi.
 * * @retval i: Yığındaki toplam eleman sayısı.
 * * @author Niyazi Han Akbulut
 * * @note Tüm listeyi gezdiği için O(N) zaman karmaşıklığına sahiptir.
 */

int say(stackptr stack) {
    int i = 0;
    Nodeptr temp = stack->bas;
    while (temp != NULL) {
        i++;
        temp = temp->forward;
    }
    return i;
}

/**
 * @brief Yığının içeriğini terminale yazdırır (Hata ayıklama / Debugging için).
 * * @param stack: Yazdırılacak yığın işaretçisi.
 * * @author Niyazi Han Akbulut
 */

void listele(stackptr stack) {
    Nodeptr temp = stack->bas;
    printf("Liste: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->forward;
    }
    printf("NULL\n");
}


/**
 * @brief Yığının en üstüne (top) yeni bir eleman ekler (LIFO prensibi).
 * * @param stack: İşlem yapılacak yığın yapısının işaretçisi.
 * @param data: Eklenecek veri.
 * * @author Niyazi Han Akbulut
 * * @note O(1) sabit zaman karmaşıklığı ile çalışır. Dışarıdan Node almak yerine
 * güvenli bellek yönetimi için Node üretimini kendi içinde (newNode) yapar.
 */

void push(stackptr stack, Nodeptr node) {
    node->forward = stack->bas;
    stack->bas = node;
}


/**
 * @brief Yığının (Stack) boş olup olmadığını kontrol eder.
 * * @param stack: Kontrol edilecek yığın işaretçisi.
 * * @retval 1 (true): Yığın boşsa veya tanımlanmamışsa (NULL).
 * @retval 0 (false): Yığında en az bir eleman varsa.
 * * @author Niyazi Han Akbulut
 */

int bosmu(stackptr stack){
    return (stack->bas==NULL);
}


/**
 * @brief Yığının en üstündeki elemanı silmeden sadece verisini okur (Gözlem kulesi).
 * * @param stack: İşlem yapılacak yığın yapısının işaretçisi.
 * * @retval -1: Yığın boşsa veya geçersiz parametre girildiyse.
 * @retval data: Yığının en üstündeki düğümün verisi.
 * * @author Niyazi Han Akbulut
 */

int peek(stackptr stack){
    if (bosmu(stack)) {
        printf("HATA: Stack bos, okunacak eleman yok!\n");
        return -1;
    }
    return stack->bas->data;
}


/**
 * @brief Yığının en üstündeki (top) elemanı çıkarır, verisini döndürür ve belleğini temizler.
 * * @param stack: İşlem yapılacak yığın yapısının işaretçisi.
 * * @retval -1: Yığın boşsa veya geçersiz parametre girildiyse.
 * @retval silinenVeri: Çıkarılan düğümün verisi.
 * * @author Niyazi Han Akbulut
 * * @note free() fonksiyonu ile memory leak (bellek sızıntısı) engellenmiştir.
 */

int pop(stackptr stack) {

    if (bosmu(stack)) {
        printf("HATA: Stack zaten bos!\n");
        return -1;
    }
    Nodeptr temp = stack->bas;
    int silinenVeri = temp->data;


    stack->bas = stack->bas->forward;


    free(temp);
    return silinenVeri;
}
/**
 * @brief Yığın içinde belirli bir değeri (Pin ID) arar.
 * * @param stack: Arama yapılacak yığın işaretçisi.
 * @param arananDeger: Bulunmak istenen değer.
 * * @retval NULL: Değer bulunamazsa veya yığın geçersizse.
 * @retval temp: Aranan değeri içeren düğümün bellek adresi.
 * * @author Niyazi Han Akbulut
 */

Nodeptr arama(stackptr stack, int arananDeger) {
    Nodeptr temp = stack->bas;
    while (temp != NULL) {
        if (temp->data == arananDeger) {
            return temp;
        }
        temp = temp->forward;
    }
    return NULL;
}




