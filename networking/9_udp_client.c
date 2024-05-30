#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65432
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(server_addr);
    int bytes_sent, bytes_received;

    // Create the UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Get the message to send to the server
    printf("Enter message to send to server: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    // Send the message to the server
    bytes_sent = sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, addr_len);
    if (bytes_sent < 0) {
        perror("sendto");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Receive the echoed message from the server
    bytes_received = recvfrom(client_socket, buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (bytes_received < 0) {
        perror("recvfrom");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_received] = '\0';
    printf("Received echoed message from server: %s\n", buffer);

    close(client_socket);
    return 0;
}
