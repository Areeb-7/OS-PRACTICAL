#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define PORT 65432
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    fd_set read_fds;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);
    int bytes_received, max_fd;

    // Create the UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the address and port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    while (1) {
        // Clear the socket set
        FD_ZERO(&read_fds);

        // Add the server socket to the set
        FD_SET(server_socket, &read_fds);
        max_fd = server_socket;

        // Wait for an activity on one of the sockets
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity < 0) {
            perror("select");
            close(server_socket);
            exit(EXIT_FAILURE);
        }

        // Check if the activity is on the server socket
        if (FD_ISSET(server_socket, &read_fds)) {
            // Receive a message from a client
            bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &addr_len);
            if (bytes_received < 0) {
                perror("recvfrom");
                close(server_socket);
                exit(EXIT_FAILURE);
            }

            buffer[bytes_received] = '\0';
            printf("Received message from client: %s\n", buffer);

            // Echo the message back to the client
            if (sendto(server_socket, buffer, bytes_received, 0, (struct sockaddr*)&client_addr, addr_len) < 0) {
                perror("sendto");
                close(server_socket);
                exit(EXIT_FAILURE);
            }
        }
    }

    close(server_socket);
    return 0;
}
