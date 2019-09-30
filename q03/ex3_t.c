#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <pthread.h>

void *printa() {
    printf("Sou filho!\n");

    pthread_exit(0);
}

int main() {
    pid_t pid = getpid();
    struct timespec before, after;
    clock_gettime(CLOCK_MONOTONIC, &before);
    pthread_t thread;
    for (int i = 0; i < 100; ++i) {
        pthread_create(&thread, NULL, printa, NULL);
        pthread_join(thread, NULL);
    }
    printf("Sou pai! %d\n", pid);
    clock_gettime(CLOCK_MONOTONIC, &after);
    long msec_diff = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_nsec - before.tv_nsec) / 1000000;
    printf("Took %ld ms", msec_diff);
}
