#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[BUFFER_SIZE];
    socklen_t client_address_len = sizeof(client_address);

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(server_socket, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is up and listening on port %d\n", PORT);

    while (1) {
        // Wait for a message from the client
        int n = recvfrom(server_socket, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_address, &client_address_len);
        buffer[n] = '\0';
        printf("Received message: %s\n", buffer);

        // Check if the client sent "exit"
        if (strcmp(buffer, "exit") == 0) {
            printf("Client sent exit command. Shutting down server.\n");
            break;
        }

        // Send response to the client
        const char *response = "Message received!";
        sendto(server_socket, response, strlen(response), 0, (const struct sockaddr *) &client_address, client_address_len);
        printf("Response sent to the client.\n");
    }

    // Close the socket
    close(server_socket);

    return 0;
}
