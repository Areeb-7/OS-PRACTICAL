#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    const char *file_path = "dummy.txt";

    mode_t new_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (chmod(file_path, new_permissions) == -1) {
        perror("chmod");
        exit(EXIT_FAILURE);
    }

    printf("File permissions changed successfully.\n");

    return 0;
}
