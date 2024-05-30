#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open a file for reading
    int fd1 = open("dummy.txt", O_RDONLY);

    // Check if file opened successfully
    if (fd1 == -1) {
        perror("Error opening file");
        return 1;
    }

    // Duplicate the file descriptor
    int fd2 = dup(fd1);

    // Check if duplication was successful
    if (fd2 == -1) {
        perror("Error duplicating file descriptor");
        close(fd1);
        return 1;
    }

    // Read from the original file descriptor
    char buffer[100];
    ssize_t bytes_read = read(fd1, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd1);
        close(fd2);
        return 1;
    }
    buffer[bytes_read] = '\0';
    printf("Read from fd1: %s\n", buffer);

    // Read from the duplicated file descriptor
    bytes_read = read(fd2, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(fd1);
        close(fd2);
        return 1;
    }
    buffer[bytes_read] = '\0';
    printf("Read from fd2: %s\n", buffer);

    // Close file descriptors
    close(fd1);
    close(fd2);

    return 0;
}
