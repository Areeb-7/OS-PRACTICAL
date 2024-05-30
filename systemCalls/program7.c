#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Size of shared memory segment

int main() {
    int shmid;
    key_t key;
    char *shm_ptr;
    char *data = "Hello, shared memory!";

    // Generate a unique key for the shared memory segment
    if ((key = ftok("shared_memory_example", 'R')) == -1) {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment
    if ((shm_ptr = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write data to the shared memory
    strncpy(shm_ptr, data, SHM_SIZE);

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process reads from shared memory
        printf("Child process reading from shared memory: %s\n", shm_ptr);
    } else {
        // Parent process waits for child to finish
        wait(NULL);
    }

    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Delete the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
