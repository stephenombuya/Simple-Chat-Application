#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"

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

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Error opening socket");
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        error("Invalid address");
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Connection failed");
    }

    printf("Connected to server. Type 'exit' to disconnect.\n");

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        trim_newline(buffer);

        if (strcmp(buffer, "exit") == 0) {
            printf("Disconnecting...\n");
            break;
        }

        if (send(sock, buffer, strlen(buffer), 0) < 0) {
            error("Error sending message");
        }

        memset(buffer, 0, BUFFER_SIZE);
        if (recv(sock, buffer, BUFFER_SIZE, 0) <= 0) {
            printf("Server disconnected\n");
            break;
        }

        printf("Server: %s\n", buffer);
    }

    close(sock);
    return 0;
}
