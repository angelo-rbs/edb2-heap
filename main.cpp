#include "heap.h"

int main() {

    MinHeap* heap = createMinHeap(10);

    insertProcess(heap, create_Process());
    insertProcess(heap, create_Process());
    insertProcess(heap, create_Process());
    insertProcess(heap, create_Process());
    insertProcess(heap, create_Process());

    printHeap(heap);

    return 0;
}