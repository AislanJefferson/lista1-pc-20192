#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int processes_qty = argc == 2 ? atoi(argv[1]) : 10000;
    printf("Programa criador de %d Processos\n", processes_qty);
    pid_t pid = getpid();
    struct timespec before, after;
    pid_t childpid[processes_qty];
    clock_gettime(CLOCK_MONOTONIC, &before);
    for (int i = 0; i < processes_qty; ++i) {
        if ((childpid[i] = fork()) == 0) {
            //printf("Sou filho! %d\n", i);
            sleep(5);
            exit(0);
        }
    }
    printf("Sou pai! %d e esperando filhos de 5 segundos\n", pid);
    for (int i = 0; i < processes_qty; ++i) {
        wait(&childpid[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    long msec_diff = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_nsec - before.tv_nsec) / 1000000;
    struct rusage usage_childs, usage_self;
    getrusage(RUSAGE_CHILDREN, &usage_childs);
    getrusage(RUSAGE_SELF, &usage_self);
    long max_memory = (usage_self.ru_maxrss + usage_childs.ru_maxrss * processes_qty) / 1024;
    printf("Took %ld ms and peak used %ldKB of memory\n", msec_diff, max_memory);
    return 0;
}
