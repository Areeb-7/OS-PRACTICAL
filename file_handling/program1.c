#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define NUM_BYTES 10

int main() {
    int file;
    char buffer[NUM_BYTES + 1];
    ssize_t bytesRead;

    
    file = open("dummy.txt", O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
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


    printf("First %d bytes: %s\n", NUM_BYTES, buffer);

    
    close(file);

    return EXIT_SUCCESS;
}
