#include <stdio.h>
#include <unistd.h>

int main() {
    // Fork the current process
    pid_t child_pid = fork();

    // Check if fork was successful
    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // This code is executed by the child process
        printf("Child process: PID is %d\n", getpid());
    } else {
        // This code is executed by the parent process
        printf("Parent process: PID is %d, Child's PID is %d\n", getpid(), child_pid);
    }

    return 0;
}
