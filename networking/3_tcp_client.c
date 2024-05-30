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

    // Create TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connect failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Get message from user
    printf("Enter message to send to server: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    // Send message to the server
    write(client_socket, buffer, strlen(buffer));

    // Receive reversed message from server
    int n = read(client_socket, buffer, BUFFER_SIZE);
    if (n < 0) {
        perror("Read failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    printf("Received reversed message from server: %s\n", buffer);

    // Close the socket
    close(client_socket);

    return 0;
}
