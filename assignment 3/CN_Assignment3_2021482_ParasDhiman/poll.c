#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <sys/poll.h>

#define PORT 8080
#define BACKLOG 4000

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

void handleClient(int clientSocket) {
    char buffer[1024];

    while (1) {
        // Receive data from the client
        int nBytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (nBytesReceived <= 0) {
            perror("recv failed");
            break;
        }

        uint64_t number;
        memcpy(&number, buffer, sizeof(uint64_t));

        // Calculate the factorial
        unsigned long long factorial = fact(number);

        // Send the factorial back to the client
        if (send(clientSocket, &factorial, sizeof(factorial), 0) < 0) {
            perror("send failed");
            break;
        }

        //printf("Factorial of %" PRIu64 " is: %llu\n", number, (unsigned long long)factorial);
    }

    close(clientSocket); // Close the client socket
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;

    struct pollfd fds[BACKLOG];
    int nfds = 1; // Initially, only the server socket is monitored

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

    // Set the server socket to be monitored for read events
    fds[0].fd = serverSocket;
    fds[0].events = POLLIN;

    while (1) {
        // Poll the file descriptors for events
        int pollResult = poll(fds, nfds, -1);
        if (pollResult < 0) {
            perror("poll failed");
            break;
        }

        // Check for events on the server socket
        if (fds[0].revents & POLLIN) {
            // Accept incoming connection
            clientAddrLen = sizeof(clientAddr);
            clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
            if (clientSocket < 0) {
                perror("accept failed");
                continue;
            }

            printf("Accepted connection from client\n");

            // Add the client socket to the pollfd array
            if (nfds < BACKLOG) {
                fds[nfds].fd = clientSocket;
                fds[nfds].events = POLLIN;
                nfds++;
            } else {
                printf("Maximum number of connections reached. Dropping incoming connection.\n");
                close(clientSocket);
            }
        }

        // Check for events on client sockets
        for (int i = 1; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                // Handle data from the client
                handleClient(fds[i].fd);

                // Remove the client socket from the pollfd array
                close(fds[i].fd);

                for (int j = i + 1; j < nfds; j++) {
                    fds[j - 1] = fds[j];
                }

                nfds--;
                i--; // Decrement i to ensure we don't skip any client sockets
            }
        }
    }

    close(serverSocket);
    return 0;
}

