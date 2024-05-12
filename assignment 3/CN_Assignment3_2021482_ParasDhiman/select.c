#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

#define PORT 8080
#define BACKLOG 10
#define MAX_CLIENTS 4000

unsigned long long fact(unsigned long long n) {
    if (n > 20) {
        n = 20;
    }

    if (n == 0) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

int main() {
    int serverSocket, clientSockets[MAX_CLIENTS], maxClients = 0;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;
    fd_set readfds, allfds;

    // Initialize the client socket array
    for (int i = 0; i < MAX_CLIENTS; i++) {
        clientSockets[i] = -1;
    }

    // Create the server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("socket creation failed");
        exit(1);
    }

    // Set up the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the address
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, BACKLOG) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    FD_ZERO(&allfds);
    FD_SET(serverSocket, &allfds);

    while (1) {
        readfds = allfds;

        // Use select to monitor file descriptors for readability
        if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) < 0) {
            perror("select error");
            exit(1);
        }

        // Check the server socket for a new connection
        if (FD_ISSET(serverSocket, &readfds)) {
            clientAddrLen = sizeof(clientAddr);
            int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket < 0) {
                perror("accept failed");
            } else {
                // Add the new client socket to the clientSockets array
                int i;
                for (i = 0; i < MAX_CLIENTS; i++) {
                    if (clientSockets[i] == -1) {
                        clientSockets[i] = clientSocket;
                        maxClients = (i > maxClients) ? i : maxClients;
                        FD_SET(clientSocket, &allfds);
                        break;
                    }
                }

                if (i == MAX_CLIENTS) {
                    printf("Too many clients. Connection rejected.\n");
                    close(clientSocket);
                }
            }
        }

        // Check all client sockets for data
        for (int i = 0; i <= maxClients; i++) {
            if (clientSockets[i] != -1 && FD_ISSET(clientSockets[i], &readfds)) {
                char buffer[1024];
                int nBytesReceived = recv(clientSockets[i], buffer, sizeof(buffer), 0);
                if (nBytesReceived <= 0) {
                    //perror("recv failed");
                    close(clientSockets[i]);
                    FD_CLR(clientSockets[i], &allfds);
                    clientSockets[i] = -1;
                } else {
                    uint64_t number;
                    memcpy(&number, buffer, sizeof(uint64_t));
                    unsigned long long factorial = fact(number);
                    if (send(clientSockets[i], &factorial, sizeof(factorial), 0) < 0) {
                        perror("send failed");
                        close(clientSockets[i]);
                        FD_CLR(clientSockets[i], &allfds);
                        clientSockets[i] = -1;
                    } else {
                        //printf("Factorial of %" PRIu64 " is: %llu\n", number, factorial);
                    }
                }
            }
        }
    }

    close(serverSocket);
    return 0;
}

