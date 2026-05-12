#include "../core/Queue.h"

int  main()
{
    kuyrukptr myQueue = newQueue();
    enqueue(myQueue, 10);
    enqueue(myQueue, 20);
    enqueue(myQueue, 30);
    enqueue(myQueue, 40);
    show(myQueue);
}