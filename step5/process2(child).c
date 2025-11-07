#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>


typedef struct {
    int multiple;
    int counter;
} shared_data_t;



union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait_op(int semid) {
    struct sembuf sops = {0, -1, 0};
    semop(semid, &sops, 1);
}

void sem_signal_op(int semid) {
    struct sembuf sops = {0, 1, 0};
    semop(semid, &sops, 1);
}

int main() {
    int shmid, semid;
    shared_data_t *shared_data;

    shmid = shmget(0x1234, sizeof(shared_data_t), 0666);


    if (shmid < 0) { 
        perror("shmget"); exit(1); 
    }

    shared_data = (shared_data_t *)shmat(shmid, NULL, 0);
    if (shared_data == (shared_data_t *)-1) { 
        perror("shmat"); exit(1); 
    }

    semid = semget(0x5678, 1, 0666);



    if (semid < 0) { 
        perror("semget"); exit(1); 
    }

    while (1) {

        sem_wait_op(semid);
        int current = shared_data->counter;
        sem_signal_op(semid);

        if (current > 100)
            break;

        usleep(100000);
    }



    while (1) {
        sem_wait_op(semid);

        if (shared_data->counter >= 500) {
            sem_signal_op(semid);
            break;

        }

        shared_data->counter++;
        int val = shared_data->counter;
        int mult = shared_data->multiple;

        if (val % mult == 0)
            printf("Process 2 - Counter %d: multple of %d\n", val, mult);
        else
            printf("Process 2 - Counter %d\n", val);

        sem_signal_op(semid);
        usleep(100000);
    }

    shmdt(shared_data);
    printf("P2 finished as counter reached -500\n");
    return 0;
}