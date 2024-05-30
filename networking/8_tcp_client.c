#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65432
#define BUFFER_SIZE 1024

void request_file(const char *file_name) {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Create the client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Receive the list of available files from the server
    printf("Available files:\n");
    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("%s", buffer);
        if (bytes_read < BUFFER_SIZE - 1) break;
    }

    // Send the file name to the server
    send(client_socket, file_name, strlen(file_name), 0);

    // Receive the file contents from the server
    while ((bytes_read = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
    }

    if (bytes_read < 0) {
        perror("recv");
    }

    close(client_socket);
}

int main() {
    char file_name[BUFFER_SIZE];

    printf("Enter the file name to request: ");
    fgets(file_name, BUFFER_SIZE, stdin);
    file_name[strcspn(file_name, "\n")] = '\0';

    request_file(file_name);

    return 0;
}
