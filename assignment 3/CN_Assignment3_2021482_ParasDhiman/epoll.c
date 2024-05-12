#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <sys/epoll.h>
#include <errno.h>

#define PORT 8080
#define MAX_EVENTS 4000

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

void handleClient(int clientSocket, int epollfd) {
    char buffer[1024];

    while (1) {
        // Receive data from the client
        int nBytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (nBytesReceived < 0) {
            if (errno == EAGAIN) {
                // No more data to read, exit the loop
                break;
            } else {
                perror("recv failed");
                close(clientSocket);
                epoll_ctl(epollfd, EPOLL_CTL_DEL, clientSocket, NULL);
                return;
            }
        } else if (nBytesReceived == 0) {
            // Client disconnected
            printf("Client disconnected\n");
            close(clientSocket);
            epoll_ctl(epollfd, EPOLL_CTL_DEL, clientSocket, NULL);
            return;
        }

        uint64_t number;
        memcpy(&number, buffer, sizeof(uint64_t));

        // Calculate the factorial
        unsigned long long factorial = fact(number);

        // Send the factorial back to the client
        if (send(clientSocket, &factorial, sizeof(factorial), 0) < 0) {
            perror("send failed");
            close(clientSocket);
            epoll_ctl(epollfd, EPOLL_CTL_DEL, clientSocket, NULL);
            return;
        }

        //printf("Factorial of %" PRIu64 " is: %llu\n", number, (unsigned long long)factorial);
    }
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen;

    struct epoll_event event, events[MAX_EVENTS];
    int epollfd;

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
    if (listen(serverSocket, MAX_EVENTS) < 0) {
        perror("listen failed");
        exit(1);
    }

    printf("Server is listening on port %d...\n", PORT);

    // Create and initialize the epoll instance
    epollfd = epoll_create(MAX_EVENTS);
    if (epollfd == -1) {
        perror("epoll_create failed");
        exit(1);
    }

    event.events = EPOLLIN;
    event.data.fd = serverSocket;

    // Add the server socket to the epoll instance
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, serverSocket, &event) == -1) {
        perror("epoll_ctl failed");
        exit(1);
    }

    while (1) {
        int numEvents = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (numEvents == -1) {
            perror("epoll_wait failed");
            exit(1);
        }

        for (int i = 0; i < numEvents; i++) {
            if (events[i].data.fd == serverSocket) {
                // Accept incoming connection
                clientAddrLen = sizeof(clientAddr);
                clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
                if (clientSocket < 0) {
                    perror("accept failed");
                    continue;
                }

                //printf("Accepted connection from client\n");

                event.events = EPOLLIN | EPOLLET;
                event.data.fd = clientSocket;

                // Add the client socket to the epoll instance
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, clientSocket, &event) == -1) {
                    perror("epoll_ctl failed");
                    exit(1);
                }
            } else {
                // Handle data from a client socket
                handleClient(events[i].data.fd, epollfd);
            }
        }
    }

    close(serverSocket);
    return 0;
}

