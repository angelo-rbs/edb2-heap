#include <stdio.h>
#include <stdlib.h>
#include "myProcess.h"
#include "heap.h"

int main(int argc, char *argv[]) {
  int n_process;
  if (argc != 2) {
    fprintf(stderr, "%s simula o gereciamento de 0 processos\n", argv[0]);
    return 1;
  }
  n_process = atoi(argv[1]);
  if (n_process <= 0) {
    fprintf(stderr, "A quantidade de processo deve ser maior que 0.\n");
    return 1;
  }
  Queue* q = nullptr;
  std::queue<Process> fila = create_queue_of_process(n_process);

  MinHeap* heap = new MinHeap(n_process);
     heap->convert_queue_to_heap(fila);

  while (!heap->isEmpty()) {
    int n = rand() % heap->getSize() + 1;

    for (int i = 0; i < n && i < heap->getSize(); ++i) {
      execute_Process(heap->nodes[i].process);
      heap->update_key(i);
    }

    while (!heap->isEmpty() && heap->peekMin().key == 0) {
      Process p = heap->extractMin().process;
      std::cout << "\n[FINALIZADO] ID=" << p.id
                << ", Programa=" << getProgramName(p.name)
                << ", TTK=" << p.time_to_kill
                << ", TU=" << p.time_used << "\n";
    }

     heap->printHeap();
  } 
  return 0;
}
