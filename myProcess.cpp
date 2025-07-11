#include "myProcess.h"
#include <cstdlib> 
#include <ctime>   
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Process& p) {
    os << "Process(ID: " << p.id << ", Program: " << getProgramName(p.name)
       << ", TTK: " << p.time_to_kill << ", TU: " << p.time_used << ")";
    return os;
}

const char* getProgramName(UnixProgram program) {
    switch (program) {
        case VI: return "vi";
        case EX: return "ex";
        case AWK: return "awk";
        case SED: return "sed";
        case CC: return "cc";
        case MAKE: return "make";
        case NROFF: return "nroff";
        case TROFF: return "troff";
        case TBL: return "tbl";
        case EQN: return "eqn";
        case YACC: return "yacc";
        case LEX: return "lex";
        case ADB: return "adb";
        case DB: return "db";
        case CSH: return "csh";
        case EMACS: return "emacs";
        case TIP: return "tip";
        case CRON: return "cron";
        case FTP: return "ftp";
        case TELNET: return "telnet";
        default: return "unknown";
    }
}

UnixProgram getRandomProgram() {
    return static_cast<UnixProgram>(rand() % PROGRAM_COUNT);
}

Process create_Process() {
    UnixProgram program = getRandomProgram();
    unsigned int id = static_cast<unsigned int>((rand() % IDMAXREF) + 1);
    unsigned int t_kill = static_cast<unsigned int>((rand() % 999) + 1);
    unsigned int t_used = 0;

    return Process(id, program, t_kill, t_used);
}

void update_used_time(Process *p, int time) {
    p->time_used = static_cast<unsigned int>(time);
}

void execute_Process(Process *p) {
    unsigned int time_in_cpu = (p->time_to_kill == 0) ? 0 : static_cast<unsigned int>((rand() % p->time_to_kill) + 1);
    update_used_time(p, time_in_cpu);
}

Queue* init_queue() {
    Queue *q = new Queue();
    q->size = 0;
    q->start = nullptr;
    q->end = nullptr;
    return q;
}

void insert_in_queue(Queue *q, const Process& p) {
    Node *n = new Node();
    n->process = p;
    n->next = nullptr;

    if (q->size == 0) {
        q->start = n;
        q->end = n;
    } else {
        q->end->next = n;
        q->end = n;
    }
    q->size++;
}

Queue* create_queue_of_process(int n) {
    Queue *q = init_queue();
    for (int i = 0; i < n; ++i) {
        Process p = create_Process();
        insert_in_queue(q, p);
    }
    return q;
}

void print_queue_of_process(Queue *q) {
    Node *wanderer = q->start;
    while (wanderer != nullptr) {
        std::cout << "Process id=" << wanderer->process.id
                  << ", Program=" << getProgramName(wanderer->process.name)
                  << ", time_to_kill=" << wanderer->process.time_to_kill
                  << ", time_used=" << wanderer->process.time_used << std::endl;
        wanderer = wanderer->next;
    }
}