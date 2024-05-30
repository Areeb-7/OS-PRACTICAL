#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];
    socklen_t server_address_len = sizeof(server_address);

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Send message to the server
    const char *message = "Hello, UDP Server!";
    printf("Sending message to the server: %s\n", message);
    sendto(client_socket, message, strlen(message), 0, (const struct sockaddr *) &server_address, server_address_len);

    // Receive response from the server
    int n = recvfrom(client_socket, (char *)buffer, BUFFER_SIZE, 0, (struct sockaddr *) &server_address, &server_address_len);
    buffer[n] = '\0';
    printf("Received response from the server: %s\n", buffer);

    // Close the socket
    printf("Closing client socket.\n");
    close(client_socket);

    return 0;
}
