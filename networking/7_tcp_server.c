#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 65432
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char file_name[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    FILE *file;
    int bytes_read;

    // Receive the file name from the client
    bytes_read = recv(client_socket, file_name, BUFFER_SIZE, 0);
    if (bytes_read < 0) {
        perror("recv");
        close(client_socket);
        return;
    }
    file_name[bytes_read] = '\0';

    // Try to open the file
    file = fopen(file_name, "rb");
    if (file == NULL) {
        char *error_message = "File not found\n";
        send(client_socket, error_message, strlen(error_message), 0);
        perror("fopen");
        close(client_socket);
        return;
    }

    // Read the file contents and send to the client
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(client_socket, buffer, bytes_read, 0);
    }

    fclose(file);
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the address and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept and handle incoming connections
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}
