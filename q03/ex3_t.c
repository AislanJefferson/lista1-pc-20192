#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
void *printa()
{
printf("Sou filho!");

pthread_exit(0);
}

int main() {
    pid_t pid = getpid();
    pthread_t thread;
    for (int i = 0; i < 100; ++i) {
        pthread_create(&thread, NULL, printa, NULL);
        pthread_join(thread, NULL);
    }
    printf("Sou pai! %d",pid);
    char i = getchar(); // soh pra fazer esperar
    return 0;
}
