#include "myProcess.h"

const char* getProgramName(UnixProgram program) {
    switch (program) {
        case VI:     return "vi";
        case EX:     return "ex";
        case AWK:    return "awk";
        case SED:    return "sed";
        case CC:     return "cc";
        case MAKE:   return "make";
        case NROFF:  return "nroff";
        case TROFF:  return "troff";
        case TBL:    return "tbl";
        case EQN:    return "eqn";
        case YACC:   return "yacc";
        case LEX:    return "lex";
        case ADB:    return "adb";
        case DB:     return "db";
        case CSH:    return "csh";
        case EMACS:  return "emacs";
        case TIP:    return "tip";
        case CRON:   return "cron";
        case FTP:    return "ftp";
        case TELNET: return "telnet";
        default:     return "unknown";
    }
}

UnixProgram getRandomProgram() {
    return (UnixProgram)(rand() % PROGRAM_COUNT);
}

Process create_Process() {
    UnixProgram program = getRandomProgram();
    unsigned int id = static_cast<unsigned int>((rand() % IDMAXREF) + 1);
    unsigned int t_kill = static_cast<unsigned int>((rand() % 999) + 1);
    unsigned int t_used = 0;
    return Process(id, program, t_kill, t_used);
}

void update_used_time(Process &p, int time) {
    p.time_used = time;
}

void execute_Process(Process &p) {
    int time_in_cpu = (rand() % p.time_to_kill) + 1;
    update_used_time(p, time_in_cpu);
}

std::queue<Process> init_queue() {
    return std::queue<Process>();
}

void insert_in_queue(std::queue<Process> &queue, Process process) {
    queue.push(process);
}

std::queue<Process> create_queue_of_process(int n) {
    std::queue<Process> queue = init_queue();
    while(queue.size() < n) {
        Process process = create_Process();
        insert_in_queue(queue, process); 
    }
    return queue;
}

// Recebe uma cópia, pop não apaga a queue original
void print_queue_of_process(std::queue<Process> queue) {
    srand((unsigned)time(NULL));
    while (! queue.empty()) {
        Process process = queue.front();
        std::cout << "Process id=" << process.id
                  << "Program=" << getProgramName(process.name)
                  << "time_to_kill=" << process.time_to_kill
                  << "time_used=" << process.time_used 
                  << std::endl;
        queue.pop();
    }
}
