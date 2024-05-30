#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

// Function to check if a number is even or odd
const char* check_even_odd(int number) {
    if (number % 2 == 0) {
        return "even";
    } else {
        return "odd";
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    
    while (1) {
        // Receive message from client
        int n = read(client_socket, buffer, BUFFER_SIZE);
        if (n <= 0) {
            perror("Read failed or client disconnected");
            break;
        }
        buffer[n] = '\0';

        // Check if the client sent "exit"
        if (strcmp(buffer, "exit") == 0) {
            printf("Client sent exit command. Closing connection.\n");
            break;
        }

        // Convert the received string to an integer
        int number = atoi(buffer);
        printf("Received number: %d\n", number);

        // Check if the number is even or odd
        const char* result = check_even_odd(number);
        printf("The number is %s\n", result);

        // Send the result back to the client
        write(client_socket, result, strlen(result));
    }

    // Close the client socket
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    // Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        // Accept an incoming connection
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        // Handle client connection
        handle_client(client_socket);
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
