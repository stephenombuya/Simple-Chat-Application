#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void *handle_client(void *client_socket) {
    int sock = *(int *)client_socket;
    char buffer[BUFFER_SIZE];

    printf("Client connected\n");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        if (recv(sock, buffer, BUFFER_SIZE, 0) <= 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("Client: %s\n", buffer);

        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        trim_newline(buffer);

        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            error("Error sending message");
        }
    }

    close(sock);
    free(client_socket);
    return NULL;
}

int main() {
    int server_sock, *client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t thread_id;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        error("Error opening socket");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Error binding socket");
    }

    if (listen(server_sock, MAX_CLIENTS) < 0) {
        error("Error listening for connections");
    }

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_sock = malloc(sizeof(int));
        *client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
        if (*client_sock < 0) {
            free(client_sock);
            error("Error accepting connection");
        }

        pthread_create(&thread_id, NULL, handle_client, (void *)client_sock);
        pthread_detach(thread_id);
    }

    close(server_sock);
    return 0;
}
