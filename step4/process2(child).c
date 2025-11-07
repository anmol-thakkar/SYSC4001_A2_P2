#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>



int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <shmid>\n", argv[0]);
        exit(1);
    }

    int shmid = atoi(argv[1]); 

    int *shared_mem = (int *)shmat(shmid, NULL, 0);
    if (shared_mem == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    int *shared_multiple = &shared_mem[0];
    int *shared_counter = &shared_mem[1];
    int cycle = 0;



    while (*shared_counter <= 100) {
        usleep(100000); 
    }




    while (*shared_counter <= 500) {
        if (*shared_counter % *shared_multiple == 0)
            printf("Process 2 - Cycle %d: shared_counter = %d is multiple of %d\n",
                   cycle, *shared_counter, *shared_multiple);
        else
            printf("Process 2 - Cycle %d: shared_counter = %d\n", cycle, *shared_counter);

        cycle++;
        usleep(100000);
    }


    shmdt(shared_mem); 
    printf("P2 finished as counter reached -500\n\n");
    return 0;
}