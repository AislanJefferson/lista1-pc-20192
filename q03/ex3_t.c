#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <pthread.h>

void *printa(void *arg) {
    printf("Sou filho! %d\n", *((int *) arg));
    free(arg);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int threads_qty = argc == 2 ? *atoi(argv[1]) : 100;
    pid_t pid = getpid();
    struct timespec before, after;
    clock_gettime(CLOCK_MONOTONIC, &before);
    pthread_t thread;
    for (int i = 0; i < threads_qty; ++i) {
        int *param = malloc(sizeof(i));
        *param = i;
        pthread_create(&thread, NULL, printa, param);
        pthread_join(thread, NULL);
    }
    printf("Sou pai! %d\n", pid);
    clock_gettime(CLOCK_MONOTONIC, &after);
    long msec_diff = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_nsec - before.tv_nsec) / 1000000;
    printf("Took %ld ms", msec_diff);
}
