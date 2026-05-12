#ifndef STACK_H
#define STACK_H



struct node {
    int data;
    struct node* forward;
};
typedef struct node Node;
typedef Node* Nodeptr;


struct Stack {
    Nodeptr bas;
};
typedef struct Stack stack;
typedef stack* stackptr;


Nodeptr newNode(int data);
stackptr yeniStack(void);
int say(stackptr stack);
void listele(stackptr stack);
void push(stackptr stack, Nodeptr node);
int peek(stackptr stack);
int bosmu(stackptr stack);
int pop(stackptr stack);
Nodeptr arama(stackptr stack, int arananDeger);


#endif