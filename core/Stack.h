#ifndef STACK_H
#define STACK_H


// Düğüm yapısı
struct node {
    int data;
    struct node* forward;
};
typedef struct node Node;
typedef Node* Nodeptr;

// Stack kontrol yapısı
struct Stack {
    Nodeptr bas;
};
typedef struct Stack stack;
typedef stack* stackptr;

// Fonksiyon Prototipleri
Nodeptr newNode(int data);
stackptr yeniStack(void);
int say(stackptr stack);
void listele(stackptr stack);
void push(stackptr stack, Nodeptr node);
int peek(stackptr stack);
int bosmu(stackptr stack);
int pop(stackptr stack); // int dönecek şekilde güncelledik (DFS için kritik)
Nodeptr arama(stackptr stack, int arananDeger);


#endif