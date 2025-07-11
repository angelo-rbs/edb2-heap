#ifndef MY_PROCESS_H
#define MY_PROCESS_H

#define IDMAXREF 500

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>


/**
 *
 * Enum para representar programas Unix
 *
 */
enum UnixProgram {
    VI,
    EX,
    AWK,
    SED,
    CC,
    MAKE,
    NROFF,
    TROFF,
    TBL,
    EQN,
    YACC,
    LEX,
    ADB,
    DB,
    CSH,
    EMACS,
    TIP,
    CRON,
    FTP,
    TELNET,
    PROGRAM_COUNT // usado para saber o total de programas
};

/**
 *
 * Função para obter o nome do programa como string
 *
 */
const char* getProgramName(UnixProgram program);

/**
 *
 * Função que pega um UnixProgram aleatoriamente
 *
 */
UnixProgram getRandomProgram();

/**
 * 
 * Estrutura para representar processos de programas Unix em execução
 *
 */
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

/**
 *
 * Função que irá criar processos de forma pseudo-aleatória
 *
 */
Process create_Process();

/**
 *
 * Função que atualiza o valor do time_used de um process
 */
void update_used_time(Process &p, int time);

/**
 *
 * Função que simula a execução de um processo p
 */
void execute_Process(Process &p);

/**
 *
 * Inicializa uma fila vazia
 *
 */
std::queue<Process> init_queue();


/**
 *
 * Insere um novo processo na fila
 *
 */
void insert_in_queue(std::queue<Process> &q, Process p);

/**
 *
 * Insere n processos aleatoriamente no fila
 *
 */
std::queue<Process> create_queue_of_process(int n);

/**
 *
 * Imprime toda a fila de processos
 *
 */
void print_queue_of_process(std::queue<Process> q);


#endif
