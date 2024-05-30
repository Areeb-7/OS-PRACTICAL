#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 12345
#define BUFFER_SIZE 1024

// Function to reverse a string
void reverse_string(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

// Function to handle each client connection
void *handle_client(void *client_socket) {
    int socket = *((int *)client_socket);
    free(client_socket);
    char buffer[BUFFER_SIZE];

    while (1) {
        // Receive message from client
        int n = read(socket, buffer, BUFFER_SIZE);
        if (n <= 0) {
            perror("Read failed or client disconnected");
            close(socket);
            pthread_exit(NULL);
        }
        buffer[n] = '\0';
        printf("Received message: %s\n", buffer);

        // Reverse the string
        reverse_string(buffer);
        printf("Reversed message: %s\n", buffer);

        // Send reversed string back to client
        write(socket, buffer, strlen(buffer));
    }

    close(socket);
    pthread_exit(NULL);
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

        // Create a new thread for each client connection
        pthread_t client_thread;
        int *new_sock = malloc(sizeof(int));
        *new_sock = client_socket;
        if (pthread_create(&client_thread, NULL, handle_client, (void *)new_sock) != 0) {
            perror("Thread creation failed");
            free(new_sock);
        } else {
            pthread_detach(client_thread); 
        }
    }

    // Close the server socket
    close(server_socket);

    return 0;
}
