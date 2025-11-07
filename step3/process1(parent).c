#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        execl("./process2", "process2", NULL);
        perror("exec failed");
        exit(1);
    } 
    else {
        int counter = 0;
        int cycle = 0;

        while (1) {
            if (counter % 3 == 0)
                printf("P1 - Cycle number: %d – %d is a multiple of 3\n", cycle, counter);
            else
                printf("P1 - Cycle number: %d\n", cycle);

            counter++;
            cycle++;
            usleep(100000);
            int status; 

            pid_t result = waitpid(pid, &status, WNOHANG);
            if (result == pid) {
                break;
            }
        }
    }

    return 0;
}