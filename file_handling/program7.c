#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    int file;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    
    file = open("example.txt", O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    
    while ((bytesRead = read(file, buffer, BUFFER_SIZE)) > 0) {
        for (int i = 0; i < bytesRead; i++) {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                printf("%s\n", buffer);
                int remainingBytes = bytesRead - (i + 1);
                if (remainingBytes > 0) {
                    for (int j = 0; j < remainingBytes; j++) {
                        buffer[j] = buffer[i + 1 + j];
                    }
                }
                break;
            } else if (i == bytesRead - 1) {
                buffer[i + 1] = '\0';
                printf("%s", buffer);
            }
        }
    }

    
    if (bytesRead == -1) {
        perror("Error reading file");
        close(file);
        return 1;
    }


    close(file);

    return 0;
}
