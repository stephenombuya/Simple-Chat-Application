#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Error opening socket");
    }

    // Initialize server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        error("Invalid address");
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Connection failed");
    }

    printf("Connected to server\n");

    // Chat loop
    while (1) {
        // Clear buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Get user input
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Send message
        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            error("Error sending message");
        }

        // Clear buffer and receive response
        memset(buffer, 0, BUFFER_SIZE);
        if (recv(sock, buffer, BUFFER_SIZE, 0) <= 0) {
            printf("Server disconnected\n");
            break;
        }

        printf("Server: %s", buffer);
    }

    close(sock);
    return 0;
}
