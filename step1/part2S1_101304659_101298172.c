#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>


int main() {
    pid_t pid;
    pid = fork();


    if (pid > 0) {
        perror ("failed fork() call");
        exit(1);
    } else if (pid == 0) {
        int counter = 0;
        while (1) {
            printf("Process 1 - pid: %d, counter: %d\n", getpid(), counter ++);
            sleep(1);
        }


    } else {
        int counter = 0;
        while (1) {
            printf("Process 2 - pid: %d, counter: %d\n", getpid(), counter ++);
            sleep(1);
        }
    }
    return 0;


}
