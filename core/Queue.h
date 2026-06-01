#ifndef QUEUE_H
#define QUEUE_H

struct node
{
    int data;
    struct node* next;
};
typedef struct node Node;
typedef Node* nodeptr;

struct kuyruk
{
    nodeptr bas;
    nodeptr son;
};
typedef struct kuyruk Kuyruk;
typedef Kuyruk* kuyrukptr;

kuyrukptr newQueue();
void enqueue(kuyrukptr k, int data);
int  dequeue(kuyrukptr k);
int isEmpty(kuyrukptr k);
int size(kuyrukptr k);
void freeQueue(kuyrukptr k);
void show(kuyrukptr k);
#endif