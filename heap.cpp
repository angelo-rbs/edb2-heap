#include "heap.h"

#include <stdlib.h>
#include <stdio.h>

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->processes.reserve(capacity);
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

int getParentIndex(int i) {
    return (i - 1) / 2;
}

int getLeftChildIndex(int i) {
    return 2 * i + 1;
}

int getRightChildIndex(int i) {
    return 2 * i + 2;
}

void swap(int i, int j, MinHeap* heap) {
    Process temp = heap->processes[i];
    heap->processes[i] = heap->processes[j];
    heap->processes[j] = temp;
}

bool isEmpty(MinHeap* heap) {
    return heap->size == 0;
}

void insertProcess(MinHeap* heap, Process process) {
    if (heap->size >= heap->capacity) {
        printf("Heap is full, cannot insert process.\n");
        return;
    }
    
    heap->processes.push_back(process);
    heap->size++;
    
    int index = heap->size - 1;
    while (index != 0 && heap->processes[getParentIndex(index)].time_to_kill > heap->processes[index].time_to_kill) {
        swap(index, getParentIndex(index), heap);
        index = getParentIndex(index);
    }
}

void printHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("Process id=%d, Program=%s, time_to_kill=%d, time_used=%d\n", 
            heap->processes[i].id, 
            getProgramName(heap->processes[i].name), 
            heap->processes[i].time_to_kill,
            heap->processes[i].time_used);
    }
}