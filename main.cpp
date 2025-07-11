#include "heap.h"
#include "myProcess.h"

int main() {

    MinHeap* heap = new MinHeap(10);

    heap->insert(create_Process(), 5);
    heap->insert(create_Process(), 4);
    heap->insert(create_Process(), 3);
    heap->insert(create_Process(), 2);
    heap->insert(create_Process(), 1);

    heap->printHeap();

    return 0;
}