//
// Created by Roi on 10/01/2023.
//

#ifndef ADV_PROG_ASS4_CLI_H
#define ADV_PROG_ASS4_CLI_H


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
#include "Command.h"
#include "Elements.h"




class CLI {
    std::vector<Command*> commands;
    Elements* elements;
    int clientSock;
    DefaultIO* dio;
    bool isUpload;
    bool isClassified;


public:
    /**
 * This method is the constructor of the CLI class. It initializes the members of the class.
 * @param clientSock The client's socket number, int type.
 */
    CLI(int clientSock);

    /**
 * This function handle the client for the server. It executes the commands according to the user's input.
 * It works in an infinity loop until the client sends '8' for closing the connection.
 */
    void start();
    /**
 *This function checks if a string us a valid input for the std::stoi method.
 * @param str the checked string.
 * @return true if the string is valid, false otherwise.
 */
    bool isValidInteger(std::string str);

    /**
 * This function is the destructor of the CLI class. It deletes all the members that are allocated on the heap.
 */
    ~CLI();

};


#endif //ADV_PROG_ASS4_CLI_H
