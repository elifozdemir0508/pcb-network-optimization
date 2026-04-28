#include<stdio.h>
#include<stdlib.h>

//kuyruktaki dugumlerin tasarimi
struct node{
    int data;
    struct node* ileri;
};
typedef struct node Node;
typedef Node* Nodeptr;

//Bir Dügüm olusturma
Nodeptr newNode(int veri){
    Nodeptr node = (Nodeptr)malloc(sizeof(Node));
    node->data=veri;
    node->ileri=NULL;
    return node;
}

//kuyruk tasarimi
struct kuyruk{
    Nodeptr bas;
    Nodeptr son;
};
typedef struct kuyruk Kuyruk;
typedef Kuyruk* Kuyrukptr;

//Bir kuyruk olusturma
Kuyrukptr newQueue(){
    Kuyrukptr k=(Kuyrukptr)malloc(sizeof(Kuyruk));
    k->bas=NULL;
    k->son=NULL;
    return k;
}

//kuyruk eleman ekleme
void enqueue(Kuyrukptr k, Nodeptr node){
    if(k->bas==NULL)
        k->bas=node;
    else
        k->son->ileri=node;
    k->son=node;
}

int isEmpty(Kuyrukptr k){
    return (k->bas == NULL);
}

//kuyruktan eleman silme
Nodeptr dequeue(Kuyrukptr k){
    Nodeptr temp=k->bas;
    if(isEmpty(k)){
        k->bas=k->bas->ileri;
        if(k->bas==NULL)
            k->son=NULL;
    }
    return temp;
}
void freeQueue(Kuyrukptr k) {
    while (!isEmpty(k)) {
        dequeue(k);
    }
    free(k);
}

//kuyruk eleman sayisini bulma
int size(Kuyrukptr k){
    Nodeptr temp=k->bas;
    int sayac=0;
    while(temp){
        sayac++;
        temp=temp->ileri;
    }
    return sayac;
}
//kuyruk yazdir
void show(Kuyrukptr k){
    Nodeptr temp = k->bas;
    while(temp){
        printf("%d --> ", temp->data);
        temp=temp->ileri;
    }
}

int main()
{
    Kuyrukptr k=newQueue();
    enqueue(k,newNode(10));
    enqueue(k,newNode(20));
    enqueue(k,newNode(30));
    enqueue(k,newNode(40));
    enqueue(k,newNode(50));
    show(k);
}