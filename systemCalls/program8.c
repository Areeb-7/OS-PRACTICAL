#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Function to perform semaphore wait operation
void sem_wait(int sem_id) {
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}

// Function to perform semaphore signal operation
void sem_signal(int sem_id) {
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}

int main() {
    int sem_id;
    key_t key;

    // Generate a unique key for the semaphore
    if ((key = ftok("semaphore_example", 'R')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create or get the semaphore
    if ((sem_id = semget(key, 1, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize the semaphore value to 1
    if (semctl(sem_id, 0, SETVAL, 1) == -1) {
        perror("semctl");
        exit(1);
    }

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        sem_wait(sem_id);
        printf("Child process: Inside critical section\n");
        sleep(2);
        printf("Child process: Exiting critical section\n");
        sem_signal(sem_id);
    } else {
        // Parent process
        sem_wait(sem_id);
        printf("Parent process: Inside critical section\n");
        sleep(2);
        printf("Parent process: Exiting critical section\n");
        sem_signal(sem_id);
        wait(NULL);
    }

    // Delete the semaphore
    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}
