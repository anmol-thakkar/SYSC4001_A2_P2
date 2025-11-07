#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("failed fork() call");
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
                printf("Cycle number: %d – %d is a multiple of 3\n", cycle, counter);
            else
                printf("Cycle number: %d\n", cycle);

            counter++;
            cycle++;
            sleep(1);
        }
    }

    return 0;
}