#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include "myProcess.h"

struct MinHeap {
    std::vector<Process> processes;
    int size;
    int capacity;
};


int getParentIndex(int i);
int getLeftChildIndex(int i);
int getRightChildIndex(int i);

MinHeap* createMinHeap(int capacity);
void insertProcess(MinHeap* heap, Process process);
bool isEmpty(MinHeap* heap);

void swap(int i, int j, MinHeap* heap);

void printHeap(MinHeap* heap);

#endif
