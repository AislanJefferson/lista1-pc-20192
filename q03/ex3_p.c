#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = getpid();
    struct timespec before, after;
    pid_t childpid;
    clock_gettime(CLOCK_MONOTONIC, &before);

    for (int i = 0; i < 100; ++i) {
        if ((childpid = fork()) == 0) {
            printf("Sou filho!\n");
            exit(0);
        } else if (childpid > 0) {
            wait(&childpid);
        }
    }
    printf("Sou pai! %d\n", pid);
    clock_gettime(CLOCK_MONOTONIC, &after);
    long msec_diff = (after.tv_sec - before.tv_sec) * 1000 + (after.tv_nsec - before.tv_nsec) / 1000000;
    printf("Took %ld ms", msec_diff);
    return 0;
}