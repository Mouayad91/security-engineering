#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

// Constant Values
#define N_DATA 2000000
#define N_SHARED 2000
#define REPEATS (N_DATA / N_SHARED)
#define SHM_ID 379401832
#define PERMISSION (SEM_A | SEM_R)
#define OP_LOCK -1
#define OP_UNLOCK 1

int sem_operation(int, int);

extern int errno;
int main(int argc, char **argv)
{
    // Used to attach the given shared memory segment to the memory space of the calling process.
    int sm_id = shmget(IPC_PRIVATE, sizeof(long int) * N_SHARED, IPC_CREAT | PERMISSION);

    int data[N_DATA];

    // Generate random number
    srand48(time(NULL));

    for (int i = 0; i < N_DATA; i++)
    {
        data[i] = lrand48();
    }

    // used to attach the given shared memory segment to the memory space of the calling process.
    int *shared = shmat(sm_id, 0, 0);

    if (*shared == -1)
    {
        fprintf(stderr, "Error attaching memory to process: %s\n", strerror(errno));
    }

    int sem_id = semget(IPC_PRIVATE, 1, PERMISSION);

    semctl(sem_id, 0, SETVAL, 1);

    int ch_pid = fork();

    if (ch_pid == 0)
    {
        printf("CHILD STARTED..\n");
        FILE *f = fopen("child_proc", "w");
        if (f == NULL)
        {
            fprintf(stderr, "Error opening file : %s\n", strerror(errno));
            exit(1);
        }

        for (int i = 0; i < REPEATS; i++)
        {
            sleep(1);
            sem_operation(sem_id, OP_LOCK);
            printf("CHILD REPEAT: %d.\n", i);
            for (int j = 0; j < N_SHARED; j++)
            {
                fprintf(f, "REPEAT: %d, SHARED %d: %d\n", i, j, shared[j]);
            }
            sem_operation(sem_id, OP_UNLOCK);
        }

        printf("CHILD FINISHED.\n");
    } else 
    {
        printf("PARENT STARTED..\n");
        for (int i = 0; i < REPEATS; i++)
        {
            sem_operation(sem_id, OP_LOCK);
            printf("PARENT REPEAT... %d.\n", i);
            for (int j = 0; j < N_SHARED; j++)
            {
                shared[j] = data[i * N_SHARED + j];
            }
            sem_operation(sem_id, OP_UNLOCK);
            sleep(1);
        }
        printf("PARENT FINISHED.\n");
    }

    return 0;
}

// Run semaphore operation on semaphore identified by id
int sem_operation(int sem_id, int operation)
{
    struct sembuf sembuffer;
    sembuffer.sem_num = 0;
    sembuffer.sem_flg = SEM_UNDO;
    sembuffer.sem_op = operation;

    if (semop(sem_id, &sembuffer, 1) == -1)
    {
        fprintf(stderr, "Error performing operations on selected semaphore : %s\n", strerror(errno));
        return -1;
    }

    return 1;
}