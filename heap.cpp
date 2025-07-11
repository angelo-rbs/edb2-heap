#include "heap.h"
#include <algorithm>
#include <limits>   
#include <iostream> 

HeapNode::HeapNode() : key(0) {}
HeapNode::HeapNode(const Process& p, unsigned int k) : process(p), key(k) {}

MinHeap::MinHeap(int capacity)
    : maxCapacity(capacity < 0 ? 0 : capacity) {
    nodes.reserve(maxCapacity);
}

MinHeap::~MinHeap() {
}

size_t MinHeap::getParentIndex(size_t i) const {
    return (i == 0) ? 0 : (i - 1) / 2;
}

size_t MinHeap::getLeftChildIndex(size_t i) const {
    return 2 * i + 1;
}

size_t MinHeap::getRightChildIndex(size_t i) const {
    return 2 * i + 2;
}

void MinHeap::swapNodes(size_t i, size_t j) {
    std::swap(nodes[i], nodes[j]);
}

void MinHeap::insert(const Process& process, unsigned int key) {
    if (nodes.size() >= (size_t)maxCapacity) {
        std::cerr << "Heap is full (max capacity: " << maxCapacity << "), cannot insert node." << std::endl;
        return;
    }

    HeapNode newNode(process, key);
    nodes.push_back(newNode);
    heapifyUp(nodes.size() - 1);
}

HeapNode MinHeap::extractMin() {
    if (isEmpty()) {
        std::cerr << "Heap is empty, cannot extract minimum node." << std::endl;
        return HeapNode(Process(), std::numeric_limits<unsigned int>::max());
    }

    HeapNode minNode = nodes[0];

    nodes[0] = nodes.back();
    nodes.pop_back();

    if (!nodes.empty()) {
        heapifyDown(0);
    }

    return minNode;
}

HeapNode MinHeap::peekMin() const {
    if (isEmpty()) {
        std::cerr << "Heap is empty, cannot peek minimum node." << std::endl;
        return HeapNode(Process(), std::numeric_limits<unsigned int>::max());
    }
    return nodes[0];
}

bool MinHeap::isEmpty() const {
    return nodes.empty();
}

size_t MinHeap::getSize() const {
    return nodes.size();
}

void MinHeap::printHeap() const {
    std::cout << "MinHeap Contents:" << std::endl;
    if (isEmpty()) {
        std::cout << "  (Empty)" << std::endl;
        return;
    }
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << "  Node " << i << ": Key=" << nodes[i].key
                  << ", Process ID=" << nodes[i].process.id
                  << ", Program=" << getProgramName(nodes[i].process.name) // Usa getProgramName
                  << ", TTK=" << nodes[i].process.time_to_kill
                  << ", TU=" << nodes[i].process.time_used << std::endl;
    }
}

void MinHeap::heapifyDown(size_t index) {
    size_t smallest = index;
    size_t leftChildIndex = getLeftChildIndex(index);
    size_t rightChildIndex = getRightChildIndex(index);

    if (leftChildIndex < nodes.size() && nodes[leftChildIndex].key < nodes[smallest].key) {
        smallest = leftChildIndex;
    }

    if (rightChildIndex < nodes.size() && nodes[rightChildIndex].key < nodes[smallest].key) {
        smallest = rightChildIndex;
    }

    if (smallest != index) {
        swapNodes(index, smallest);
        heapifyDown(smallest);
    }
}

void MinHeap::heapifyUp(size_t index) {
    while (index > 0 && nodes[getParentIndex(index)].key > nodes[index].key) {
        swapNodes(index, getParentIndex(index));
        index = getParentIndex(index);
    }
}

void MinHeap::update_key(size_t index) {
    if (index >= nodes.size()) return;
    nodes[index].key = nodes[index].process.time_to_kill - nodes[index].process.time_used;
    heapifyUp(index);
    heapifyDown(index);
}

void MinHeap::convert_queue_to_heap(std::queue<Process> fila) {
    while (!fila.empty()) {
        Process p = fila.front(); fila.pop();
        unsigned int key = p.time_to_kill - p.time_used;
        insert(p, key);
    }
}

std::queue<Process> MinHeap::convert_heap_to_queue() const {
    std::queue<Process> fila;
    for (const auto& node : nodes) {
        fila.push(node.process);
    }
    return fila;
}
