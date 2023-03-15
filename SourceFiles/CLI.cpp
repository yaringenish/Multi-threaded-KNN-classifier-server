//
// Created by Roi on 10/01/2023.
//

#include "CLI.h"
#include "DefaultIO.h"
#include "SocketIO.h"
#include "CommandBegin.h"
#include "Upload.h"
#include <string.h>
#include <vector>
#include "Parameters.h"
#include "Elements.h"
#include "Command.h"
#include "Classification.h"
#include "PreparedVectors.h"
#include "ResultFile.h"

/**
 * This method is the constructor of the CLI class. It initializes the members of the class.
 * @param clientSock The client's socket number, int type.
 */
CLI::CLI(int clientSock) {
    this->clientSock = clientSock;
    this->dio = new SocketIO(clientSock);
    this->commands.push_back(new CommandBegin(this->dio));
    this->commands.push_back(new Upload(this->dio));
    this->commands.push_back(new Parameters(this->dio));
    this->commands.push_back(new Classification());
    this->commands.push_back(new PreparedVectors());
    this->commands.push_back(new ResultFile());
    this->elements = new Elements();
    this->isUpload = false;
    this->isClassified = false;
}

/**
 * This function is the destructor of the CLI class. It deletes all the members that are allocated on the heap.
 */
CLI::~CLI() {
    for (int i = 0; i < 6; ++i) {
        delete(this->commands.at(i));
    }
    delete(this->dio);
    delete(this->elements);
}

/**
 *This function checks if a string us a valid input for the std::stoi method.
 * @param str the checked string.
 * @return true if the string is valid, false otherwise.
 */
bool CLI::isValidInteger(std::string str){
    int length = str.length();
    for(int i = 0; i < length;i++) {
        if(!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}


/**
 * This function handle the client for the server. It executes the commands according to the user's input.
 * It works in an infinity loop until the client sends '8' for closing the connection.
 */
void CLI::start(){
    // sends the menu to the server.
    commands[0]->execute(this->elements);
    // gets user's input
    std::string s = this->dio->read();
    int choose = 0;
    choose = std::stoi(s);
    bool isDone = false;
    bool is3Already = false;
    bool is4Already = false;
    bool is5Already = false;
    while(true) {
        switch(choose) {
            case 1:
                commands[1]->execute(this->elements);
                if(this->elements->getIsUpload()) {
                    this->isUpload = true;
                }
                else{
                    this->isUpload = false;
                }
                this->isClassified = false;
                break;

            case 2:
                commands[2]->execute(this->elements);
                break;
            case 3:
                //checks that the user uploaded the data
                if(isUpload) {
                    if(!is3Already) {
                        this->commands[3] = new Classification(this->dio, this->elements->getFv(), this->elements->getDistType(), this->elements->getK());
//                        this->commands.push_back(new Classification(this->dio, this->elements->getFv(), this->elements->getDistType(), this->elements->getK()));
                        this->commands[3]->execute(this->elements);


                        is3Already = true;
                        this->isClassified = true;
                    }
                    else{
                        this->commands[3] = new Classification(this->dio, this->elements->getFv(), this->elements->getDistType(), this->elements->getK());
                        this->commands[3]->execute(this->elements);
                        this->isClassified = true;
                    }

                }
                else {
                    std::string str = "please upload data\n";
                    this->dio->write(str);
                }
                break;
            case 4:
                //checks that the user uploaded and classified the data
                if(this->isUpload && this->isClassified) {
                    if(!is4Already) {
                        this->commands[4] = new PreparedVectors(this->dio, this->elements->getClassifiedVectors());
//                        this->commands.push_back(new PreparedVectors(this->dio, this->elements->getClassifiedVectors()));
                        this->commands[4]->execute(this->elements);
                        is4Already = true;
                        break;
                    }
                    else {
                        this->commands[4] = new PreparedVectors(this->dio, this->elements->getClassifiedVectors());
                        this->commands[4]->execute(this->elements);
                        break;
                    }
                }
                else {
                    if(!this->isUpload) {
                        std::string str = "please upload data\nplease\n";
                        this->dio->write(str);
                        break;
                    }
                    else {
                        std::string str = "please classify the data\nplease\n";
                        this->dio->write(str);
                        break;
                    }
                }
            case 5:
                if(this->isUpload && this->isClassified) {
                    if(!is5Already) {
                        this->commands[5] = new ResultFile(this->dio, this->elements->getClassifiedVectors());
//                        this->commands.push_back(new ResultFile(this->dio, this->elements->getClassifiedVectors()));
                        this->commands[5]->execute(this->elements);
                        is5Already = true;
                        break;
                    }
                    else{

                        this->commands[5] = new ResultFile(this->dio, this->elements->getClassifiedVectors());
                        this->commands[5]->execute(this->elements);
                        is5Already = true;
                        break;
                    }

                }
                else {
                    std::string please = "please\n";
                    if(!this->isUpload) {
                        this->dio->write(please);
                        std::string str = "please upload data\n";
                        this->dio->write(str);

                        break;
                    }
                    else {
                        this->dio->write(please);
                        std::string str = "please classify the data\n";
                        this->dio->write(str);
                        break;
                    }
                }
            case 8:
                isDone = true;
                break;
        }
        if(isDone) {
            break;
        }
        // gets another input from the client.
        std::string s = this->dio->read();
        choose = std::stoi(s);
    }
}