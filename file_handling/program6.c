#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int file;

    
    file = open("dummy.txt", O_WRONLY | O_APPEND);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    
    if (dprintf(file, "End of File\n") < 0) {
        perror("Error writing to file");
        close(file);
        return 1;
    }

    
    close(file);

    printf("Data appended to file successfully.\n");
    
    return 0;
}
