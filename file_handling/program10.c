#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main() {
    
    char filename[100];
    scanf("%s", filename);

    
    int fd = open(filename, O_RDONLY);

    
    if (fd != -1) {
        printf("File exists.\n");
        
        close(fd);
    } else {
        printf("File does not exist or cannot be opened.\n");
    }

    return 0;
}
