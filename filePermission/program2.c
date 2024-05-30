#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *file_path = "dummy.txt";
    uid_t new_owner_uid = 1001; 
    gid_t new_owner_gid = 1001;

    if (chown(file_path, new_owner_uid, new_owner_gid) == -1) {
        perror("chown");
        exit(EXIT_FAILURE);
    }

    printf("File owner changed successfully.\n");

    return 0;
}
