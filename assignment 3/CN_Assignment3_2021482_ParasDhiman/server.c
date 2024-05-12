#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>

#define PORT 8080
#define BACKLOG 10

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
            //perror("recv failed");
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

    while (1) {
        // Accept incoming connection
        clientAddrLen = sizeof(clientAddr);
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket < 0) {
            perror("accept failed");
            continue;
        }

        //printf("Accepted connection from client\n");

        // Create a child process to handle the client
        int pid = fork();
        if (pid == 0) {
            // Child process
            close(serverSocket); // Close the listening socket in the child process
            handleClient(clientSocket);
            exit(0);
        } else if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else {
            // Parent process
            close(clientSocket); // Close the client socket in the parent process
        }
    }

    close(serverSocket);
    return 0;
}

