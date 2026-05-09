#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

//stack tasarımı


Nodeptr newNode(int data) {
    Nodeptr n = (Nodeptr)malloc(sizeof(Node));
    if (n != NULL) {
        n->data = data;
        n->forward = NULL;
    }
    return n;
}

stackptr yeniStack(void) {
    stackptr s1 = (stackptr)malloc(sizeof(stack));
    if (s1 != NULL) {
        s1->bas = NULL;
    }
    return s1;
}

int say(stackptr stack) {
    int i = 0;
    Nodeptr temp = stack->bas;
    while (temp != NULL) {
        i++;
        temp = temp->forward;
    }
    return i;
}

void listele(stackptr stack) {
    Nodeptr temp = stack->bas;
    printf("Liste: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->forward;
    }
    printf("NULL\n");
}

void push(stackptr stack, Nodeptr node) {
    node->forward = stack->bas;
    stack->bas = node;
}
int bosmu(stackptr stack){
    return (stack->bas==NULL);
}

int peek(stackptr stack){
    if (bosmu(stack)) {
        printf("HATA: Stack bos, okunacak eleman yok!\n");
        return -1;
    }
    return stack->bas->data;
}

int pop(stackptr stack) {
    // 1. Stack boşsa hata döndür
    if (bosmu(stack)) {
        printf("HATA: Stack zaten bos!\n");
        return -1;
    }
    Nodeptr temp = stack->bas;
    int silinenVeri = temp->data;

    // 3. Stack'in başını bir sonrakine kaydır
    stack->bas = stack->bas->forward;

    // 4. Eski düğümü bellekten sil ve veriyi döndür
    free(temp);
    return silinenVeri;
}

Nodeptr arama(stackptr stack, int arananDeger) {
    Nodeptr temp = stack->bas;
    while (temp != NULL) {
        if (temp->data == arananDeger) {
            return temp; // Bulundu
        }
        temp = temp->forward;
    }
    return NULL; // Bulunamadi
}




