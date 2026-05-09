#include <stdio.h>
#include "../core/Stack.h"

int main(int argc, const char * argv[]) {
    stackptr listem = yeniStack();

    push(listem, newNode(30));
    push(listem, newNode(20));
    push(listem, newNode(10));


    printf("Ekleme islemleri sonrasi:\n");
    listele(listem);
    printf("Eleman Sayisi: %d\n\n", say(listem));
    pop(listem);
    printf("Cikarma islemleri sonrasi:\n");
    listele(listem);
    return 0;
}