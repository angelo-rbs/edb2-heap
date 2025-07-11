#ifndef MY_PROCESS_H
#define MY_PROCESS_H

#include <string>
#include <iostream>
#include <vector>

#define IDMAXREF 500

typedef enum {
    VI, EX, AWK, SED, CC, MAKE, NROFF, TROFF, TBL, EQN, YACC, LEX, ADB, DB,
    CSH, EMACS, TIP, CRON, FTP, TELNET, PROGRAM_COUNT // usado para saber o total de programas
} UnixProgram;

const char* getProgramName(UnixProgram program);

UnixProgram getRandomProgram();

struct Process {
    unsigned int id;
    UnixProgram name;
    unsigned int time_to_kill;
    unsigned int time_used;

    Process() : id(0), name(PROGRAM_COUNT), time_to_kill(0), time_used(0) {}
    Process(unsigned int _id, UnixProgram _name, unsigned int _ttk, unsigned int _tu)
        : id(_id), name(_name), time_to_kill(_ttk), time_used(_tu) {}

    friend std::ostream& operator<<(std::ostream& os, const Process& p);
};

Process create_Process();

void update_used_time(Process *p, int time);

void execute_Process(Process *p);

typedef struct node {
    Process process;
    struct node *next;
} Node;

typedef struct {
    int size;
    Node *start;
    Node *end;
} Queue;

Queue* init_queue();

void insert_in_queue(Queue *q, const Process& p); // Passagem por referência constante

Queue* create_queue_of_process(int n);

void print_queue_of_process(Queue *q);


#endif