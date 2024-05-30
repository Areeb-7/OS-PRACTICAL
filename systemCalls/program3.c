#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid;

    // Fork a child process
    child_pid = fork();

    if (child_pid == -1) {
        // Error occurred
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process: PID is %d\n", getpid());
        sleep(2); // Simulate some work in the child process
        exit(EXIT_SUCCESS);
    } else {
        // This code is executed by the parent process
        printf("Parent process: PID is %d, Child's PID is %d\n", getpid(), child_pid);

        // Parent process waits for the child to terminate
        int status;
        pid_t terminated_child_pid = wait(&status);

        if (terminated_child_pid == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Parent process: Child process %d terminated with exit status %d\n",
                   terminated_child_pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Parent process: Child process %d terminated by signal %d\n",
                   terminated_child_pid, WTERMSIG(status));
        }
    }

    return 0;
}
