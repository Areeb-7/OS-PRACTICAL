#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function
void sigint_handler(int signum) {
    printf("Signal SIGINT received. Exiting...\n");
    exit(signum);
}

int main() {
    // Register the signal handler for SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
        perror("signal");
        return 1;
    }

    printf("Press Ctrl+C to send SIGINT...\n");

    // Infinite loop to keep the program running
    while (1) {
        sleep(1);
    }

    return 0;
}
