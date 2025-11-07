#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

// seperate files or not?????????

int main() {
    pid_t pid;
    pid = fork();

    if (pid > 0) {
        perror ("failed fork() call");
        exit(1);
    } else if (pid == 0) {
        exec1("./process2", "process2", NULL);
        perror("exec failed");
        exit(1);
        
    } else {
        exec1("./process1", "process1", NULL);
        perror("exec failed");
        exit(1);
        
    }
    return 0;

}