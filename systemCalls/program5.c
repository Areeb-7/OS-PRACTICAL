#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    // File descriptors for the pipe
    int pipe_fds[2]; 

    // Create the pipe
    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid_t child_pid = fork(); 

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Close the write end of the pipe
        close(pipe_fds[1]); 

        char buffer[BUFFER_SIZE];
        ssize_t num_bytes_read;

        // Read data from the pipe
        num_bytes_read = read(pipe_fds[0], buffer, BUFFER_SIZE);
        if (num_bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Child process received message from parent: %s\n", buffer);

        // Close the read end of the pipe
        close(pipe_fds[0]); 
    } else {
        // Close the read end of the pipe
        close(pipe_fds[0]); 

        char message[] = "Hello from parent process!";
        
        // Write data to the pipe
        if (write(pipe_fds[1], message, sizeof(message)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Close the write end of the pipe
        close(pipe_fds[1]); 
    }

    return 0;
}
