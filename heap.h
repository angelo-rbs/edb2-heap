#ifndef HEAP_H
#define HEAP_H

#include <vector>   
#include <string>   
#include <iostream> 
#include "myProcess.h"

typedef struct HeapNode {
    Process process;    
    unsigned int key;   

    HeapNode();
    HeapNode(const Process& p, unsigned int k);
} HeapNode;

class MinHeap {
public:
    MinHeap(int maxCapacity);
    ~MinHeap();

    bool isEmpty() const;
    size_t getSize() const;
    void insert(const Process& process, unsigned int key);
    HeapNode extractMin();
    HeapNode peekMin() const;

    void printHeap() const;

    void update_key(size_t index);
    void convert_queue_to_heap(std::queue<Process> fila);
    void convert_heap_to_queue() const; 

private:
    std::vector<HeapNode> nodes;
    const int maxCapacity;      

    size_t getParentIndex(size_t i) const;
    size_t getLeftChildIndex(size_t i) const;
    size_t getRightChildIndex(size_t i) const;
    void swapNodes(size_t i, size_t j);
    void heapifyDown(size_t index);     
    void heapifyUp(size_t index);       
};

#endif
