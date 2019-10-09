#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int processes_qty = argc == 2 ? atoi(argv[1]) : 100;
    pid_t pid = getpid();
    struct timespec before, after;
    pid_t childpid[processes_qty];
    clock_gettime(CLOCK_MONOTONIC, &before);

    for (int i = 0; i < processes_qty; ++i) {
        if ((childpid[i] = fork()) == 0) {
            printf("Sou filho! %d\n", i);
            sleep(10);
            exit(0);
        }
    }
    printf("Sou pai! %d\n", pid);
    for (int i = 0; i < processes_qty; ++i) {
        wait(&childpid[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &after);
    long msec_diff = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_nsec - before.tv_nsec) / 1000000;
    printf("Took %ld ms", msec_diff);
    return 0;
}
