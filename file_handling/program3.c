#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_BYTES 10

int main() {
    int file;
    off_t file_size;
    char buffer[NUM_BYTES + 1];
    ssize_t bytesRead;

    
    file = open("dummy.txt", O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    
    file_size = lseek(file, 0, SEEK_END);
    if (file_size == -1) {
        perror("Error getting file size");
        close(file);
        return EXIT_FAILURE;
    }

    
    if (file_size < NUM_BYTES) {
        fprintf(stderr, "File is smaller than %d bytes.\n", NUM_BYTES);
        close(file);
        return EXIT_FAILURE;
    }

    
    off_t offset = lseek(file, -NUM_BYTES, SEEK_END);
    if (offset == -1) {
        perror("Error setting file pointer");
        close(file);
        return EXIT_FAILURE;
    }

    
    bytesRead = read(file, buffer, NUM_BYTES);
    if (bytesRead < NUM_BYTES) {
        if (bytesRead == 0) {
            printf("End of file reached.\n");
        } else if (bytesRead == -1) {
            perror("Error reading file");
            close(file);
            return EXIT_FAILURE;
        }
    }

    
    buffer[bytesRead] = '\0';

    
    printf("Last %d bytes: %s\n", NUM_BYTES, buffer);

    
    close(file);

    return EXIT_SUCCESS;
}
