#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    int file_descriptor;

    
    file_descriptor = open("example.txt", O_RDONLY);
    if (file_descriptor == -1) {
        perror("Error opening file in read-only mode");
        return EXIT_FAILURE;
    }
    printf("File opened in read-only mode.\n");
    close(file_descriptor);

    
    file_descriptor = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_descriptor == -1) {
        perror("Error opening file in write-only mode");
        return EXIT_FAILURE;
    }
    printf("File opened in write-only mode.\n");
    close(file_descriptor);

    
    file_descriptor = open("example.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (file_descriptor == -1) {
        perror("Error opening file in append-only mode");
        return EXIT_FAILURE;
    }
    printf("File opened in append-only mode.\n");
    close(file_descriptor);

    
    file_descriptor = open("example.txt", O_RDWR);
    if (file_descriptor == -1) {
        perror("Error opening file in read/write mode");
        return EXIT_FAILURE;
    }
    printf("File opened in read/write mode.\n");
    close(file_descriptor);

    return EXIT_SUCCESS;
}
