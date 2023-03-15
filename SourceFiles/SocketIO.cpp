//
// Created by yarin on 09/01/2023.
//

#include "SocketIO.h"
#include "DefaultIO.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
/**
 * constructor
 * @param clientID int - socket number of the wanted client
 */
SocketIO::SocketIO(int clientID): DefaultIO(clientID) {}

/**
 * distractor
 */
SocketIO::~SocketIO(){}

/**
 * sending to the client's socket the wanted string string
 * @param s the wanted string to send the client
 */
void SocketIO::write(std::string s){
    const char* buffer = s.c_str();
    send(this->clientID,buffer,strlen(buffer),0);
}
/**
 * receiving from the tcp buffer char by char.
 * @return the first string we took from the tcp buffer that ends with the char '\n\.
 */
std::string SocketIO::readByChar(){
    char b = 0;
    std:: string s = "";
    int expected_data_len = sizeof(b);
    int read_bytes;
    while(b != '\n'){
        read_bytes = recv(this->clientID, &b, expected_data_len, 0);
        if(read_bytes < 0){
            perror("error receiving from client");
            std::exit(0);
        }
        else{
            if(b != '\n') {
                s+=b;
            }
        }
    }
    return s;
}
/**
 * taking from the tcp buffer as much as we can till the size of 4096 bytes.
 * @return the current tcp buffer content as string(maximum size of 4096 bytes).
 */
std::string SocketIO::read(){
    char b [4096] = {0};
    int expected_data_len = sizeof(b);
    // receives message from the server
    int read_bytes = recv(clientID, b, expected_data_len, 0);
    // checks that the message gets the message correctly
    if(read_bytes < 0){
        perror("error receiving from client");
        std::exit(0);
    }
    std::string s = DefaultIO::convertToString(b, read_bytes);
    return s;
}