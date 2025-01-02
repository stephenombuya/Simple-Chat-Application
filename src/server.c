#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // Create socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        error("Error opening socket");
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Error binding socket");
    }

    // Listen for connections
    listen(server_sock, 5);
    printf("Server listening on port %d...\n", PORT);

    // Accept connection
    client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0) {
        error("Error accepting connection");
    }

    printf("Client connected\n");

    // Chat loop
    while (1) {
        // Clear buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Receive message
        if (recv(client_sock, buffer, BUFFER_SIZE, 0) <= 0) {
            printf("Client disconnected\n");
            break;
        }

        printf("Client: %s", buffer);

        // Get server response
        printf("Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send response
        if (send(client_sock, buffer, strlen(buffer), 0) < 0) {
            error("Error sending message");
        }
    }

    // Close sockets
    close(client_sock);
    close(server_sock);
    return 0;
}
