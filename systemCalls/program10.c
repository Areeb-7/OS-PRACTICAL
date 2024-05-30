#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Signal handler function for SIGINT
void sigint_handler(int signum) {
    printf("\nSIGINT received. Exiting...\n");
    exit(signum);
}

int main() {
    // Register the signal handler for SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Press Ctrl+C to send SIGINT signal...\n");

    // Infinite loop to keep the program running
    while (1) {
    }

    return 0;
}
