#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int file;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;
    int lineCount = 0;

    
    file = open("example.txt", O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    
    while ((bytesRead = read(file, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                lineCount++;
            }
        }
    }

    
    if (bytesRead == -1) {
        perror("Error reading file");
        close(file);
        return 1;
    }

    
    close(file);

    
    if (bytesRead > 0 && buffer[bytesRead - 1] != '\n') {
        lineCount++;
    }

    printf("Number of lines in the file: %d\n", lineCount);

    return 0;
}
