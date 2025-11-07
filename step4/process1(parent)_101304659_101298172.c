#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>



int main() {
    int shmid = shmget(IPC_PRIVATE, 2 * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0) 
    {
        perror("shmget failed");
        exit(1);
    }


    int *shared_mem = (int *)shmat(shmid, NULL, 0);
    if (shared_mem == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    int *shared_multiple = &shared_mem[0]; 
    int *shared_counter = &shared_mem[1]; 
    
    // chanagble multiple 
    *shared_multiple = 5;  
    *shared_counter = 0;   

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        char shmid_str[16];
        sprintf(shmid_str, "%d", shmid);
        execl("./process2", "process2", shmid_str, NULL);
        perror("exec failed");
        exit(1);
    } 
    else {
        int cycle = 0;

        while (*shared_counter <= 500) {
            if (*shared_counter % *shared_multiple == 0)
                printf("Process 1 - Cycle %d: shared_counter = %d is multple of %d\n",
                       cycle, *shared_counter, *shared_multiple);
            else
                printf("Process 1 - Cycle %d: shared_counter = %d\n", cycle, *shared_counter);

            (*shared_counter)++;
            cycle++;
            usleep(100000);      
        }

        wait(NULL); 

        shmdt(shared_mem);             
        shmctl(shmid, IPC_RMID, NULL); 

        printf("P1 finished as counter reached -500\n\n");
    }

    return 0;
}