#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "Knn.h"
#include "KnnEuclidean.h"
#include "KnnManhattan.h"
#include "KnnChebyshev.h"
#include "KnnCanberra.h"
#include "KnnMinkowski.h"
#include "FileValidate.h"
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include <thread>
#include "CLI.h"


/**
 * checks that the arguments from the command line are valid.
 * @param argv the char** array from the command line.
 */
void areArgumentsValid(char** argv) {
    // port check
    if (argv[1] == nullptr) {
        std::cout << "invalid arguments" << std::endl;
        std::exit(0);
    } else {
        // checks there are only digits in the given port.
        for (int i = 0; i < strlen(argv[1]); i++) {
            if (!std::isdigit(argv[1][i])) {
                std::cout << "invalid arguments" << std::endl;
                std::exit(0);
            }
            int check =  std::stoi(argv[1]);
            // checks that the port is in the valid range.
            if(check > 65535 || check < 1024){
                std::cout << "invalid arguments" << std::endl;
                std::exit(0);
            }
        }
    }
}


/**
 * This function handles each client by creating CLI and taking care in all client's needs.
 * @param clientSock  int type, represent the client number socket
 */
void handle(int clientSock) {
    CLI cli = CLI(clientSock);
    cli.start();
    close(clientSock);
}

/**
 * This is the main method of the server. It accepts new clients on the main thread and for each client set a handle function with the server's socket
 * for this specific client. Handle function creates on the new thread a CLI object which plays a rule as a sub server that dealing only with this
 * specific client requests.
 * client the classification of the vector.
 * @param argc int array.
 * @param argv char** array
 * @return -
 */
int main(int argc, char** argv) {
    // checks if the command line's arguments are valid.
    areArgumentsValid(argv);
    const int server_port = std::stoi(argv[1]);
    // creates socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        std::exit(0);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    // binds the server's socket to the given port number
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        std::exit(0);

    }
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
        std::exit(0);

    }
    std::vector <std::thread> threads;
    while (true) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
        }
        threads.emplace_back(std::thread(handle, client_sock));
    }
    return 0;
}



