#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_SIZE 256
#define MSG_TYPE 1

// Define structure for message
struct message_buffer {
    long msg_type;
    char msg_text[MSG_SIZE];
};

int main() {
    key_t key;
    int msg_id;
    struct message_buffer message;

    // Generate a unique key
    key = ftok("msg_queue_key", 'A');

    // Create a message queue
    msg_id = msgget(key, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Prompt user to enter a message
    printf("Enter a message to send: ");
    fgets(message.msg_text, MSG_SIZE, stdin);
    message.msg_type = MSG_TYPE;

    // Send the message
    if (msgsnd(msg_id, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Message sent: %s", message.msg_text);

    // Receive the message
    if (msgrcv(msg_id, &message, sizeof(message), MSG_TYPE, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    printf("Received message: %s", message.msg_text);

    // Close the message queue
    if (msgctl(msg_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
