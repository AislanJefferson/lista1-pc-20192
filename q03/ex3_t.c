#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>

void *printa(void *arg) {
    //printf("Sou filho! %d\n", *((int *) arg));
    free(arg);
    sleep(5);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int threads_qty = argc == 2 ? atoi(argv[1]) : 100;
    printf("Programa criador de %d Threads\n", threads_qty);
    pid_t pid = getpid();
    struct timespec before, after;
    clock_gettime(CLOCK_MONOTONIC, &before);
    pthread_t thread[threads_qty];
    for (int i = 0; i < threads_qty; ++i) {
        int *param = malloc(sizeof(i));
        *param = i;
        pthread_create(&thread[i], NULL, printa, param);
    }
    printf("Sou pai! %d e esperando filhos de 5 segundos\n", pid);
    for (int i = 0; i < threads_qty; ++i) {
        pthread_join(thread[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    long msec_diff = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_nsec - before.tv_nsec) / 1000000;
    struct rusage usage_childs, usage_self;
    getrusage(RUSAGE_CHILDREN, &usage_childs);
    getrusage(RUSAGE_SELF, &usage_self);
    long max_memory = (usage_self.ru_maxrss + usage_childs.ru_maxrss) / 1024;
    printf("Took %ld ms and peak used %ldKB of memory\n", msec_diff, max_memory);
}

