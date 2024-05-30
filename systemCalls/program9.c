#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process executing another program...\n");
        // Replace current process image with a new program
        // Change "ls" to the program you want to execute
        if (execl("/bin/ls", "ls", "-l", NULL) == -1) {
            perror("execl");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        printf("Parent process waiting for the child to finish...\n");
        wait(NULL);
        printf("Child process finished execution.\n");
    }

    return 0;
}
