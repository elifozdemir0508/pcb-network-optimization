#include<stdio.h>
#include<stdlib.h>
#include"Queue.h"


//Bir Dügüm olusturma
static nodeptr newNode(int veri){
    nodeptr node = (nodeptr)malloc(sizeof(Node));
    node->data=veri;
    node->next=NULL;
    return node;
}


//Bir kuyruk olusturma
kuyrukptr newQueue(){
    kuyrukptr k=(kuyrukptr)malloc(sizeof(Kuyruk));
    k->bas=NULL;
    k->son=NULL;
    return k;
}

//kuyruk eleman ekleme
void  enqueue(kuyrukptr k, int veri){
    nodeptr node = newNode(veri);
    if(k->bas==NULL)
        k->bas= node;
    else
        k->son->next=node;
    k->son= node;
   }

int isEmpty(kuyrukptr k){
    return (k->bas == NULL);
}

//kuyruktan eleman silme
int dequeue(kuyrukptr k) {
    if(isEmpty(k)) {
        printf("Hata!:Kuyruk boş\n");
        return -1;
    }
    nodeptr temp = k->bas;
    int cikan_veri = temp->data; // Çıkan Pin ID'si

    k->bas = k->bas->next;
    if(k->bas == NULL) {
        k->son = NULL;
    }
    free(temp);
    return cikan_veri;
}

    void freeQueue(kuyrukptr k) {
        while (!isEmpty(k)) {
            dequeue(k);
        }
        free(k);
    }

    //kuyruk eleman sayisini bulma
    int size(kuyrukptr k){
        nodeptr temp=k->bas;
        int sayac=0;
        while(temp){
            sayac++;
            temp=temp->next;
        }
        return sayac;
    }
    //kuyruk yazdir
    void show(kuyrukptr k){
        nodeptr temp = k->bas;
        while(temp){
            printf("%d --> ", temp->data);
            temp=temp->next;
        }
    printf("\n");
    }



