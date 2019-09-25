#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <sys/wait.h>
int main() {
    pid_t pid = getpid();
    pid_t childpid;
    for (int i = 0; i < 100; ++i) {
        if((childpid =  fork()) == 0){
            printf("Sou filho!");
            exit(0);
        }else if(childpid > 0){
           wait(&childpid);
        }
    }
    printf("Sou pai! %d",pid);
    char i = getchar(); // soh pra fazer esperar
    return 0;
}
