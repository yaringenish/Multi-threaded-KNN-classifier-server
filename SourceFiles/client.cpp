#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include <fstream>
#include<iostream>
#include<string>
#include <dirent.h>
#include <thread>
#include <vector>

/**
 * This function receives messages from the server, and ends when it gets '\n'.
 * It concat the chars to the full message and returns it as a string.
 * @param sock int type, the server's socket number
 * @return the full message, string type.
 */
std::string readByChar(int sock){
    char b = 0;
    std:: string s = "";
    int expected_data_len = sizeof(b);
    int read_bytes;
    while(b != '\n'){
        read_bytes = recv(sock, &b, expected_data_len, 0);
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
 * This function checks if a string is a valid input for std::stoi
 * @param str string type
 * @return true if the string is valid, false otherwise.
 */
bool isValidInteger(std::string str){
    int length = str.length();
    if(str.length() == 0) {
        return false;
    }
    for(int i = 0; i < length;i++) {
        if(!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
/**
 * This method checks if the IP address that the user entered in the command line is valid
 * @param str std::string type.
 * @return true if the IP is valid, false otherwise.
 */
bool isIpValid(std::string str) {
    int dotsCount = 0;
    // counts the dots
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            dotsCount++;
        }
    }
    if(dotsCount != 3) {
        return false;
    }
    std::stringstream src(str);
    std::string temp;
    while (std::getline(src, temp, '.')) {
        // checks if the sub strings are only numbers.
        for(int i = 0; i < temp.size(); i++) {
            if(! std::isdigit(temp[i])) {
                return false;
            }
        }
        int num = std::stoi(temp);
        // checks if the numbers are in the valid range.
        if(num < 0 || num > 255) {
            return false;
        }
    }
    return true;
}
/**
 * This function checks if the user's arguments from the command line are valid.
 * @param argv char** array from command line
 */
void areArgumentsValid(char** argv) {
    // ip check
    if(argv[1] == nullptr){
        std::cout << "invalid arguments" << std::endl;
        std::exit(0);
    }
    else{
        if(!isIpValid(argv[1])){
            std::cout << "invalid arguments" << std::endl;
            std::exit(0);
        }
    }
    // port check
    if (argv[2] == nullptr) {
        std::cout << "invalid arguments" << std::endl;
        std::exit(0);
    } else {
        for (int i = 0; i < strlen(argv[2]); i++) {
            if (!std::isdigit(argv[2][i])) {
                std::cout << "invalid arguments" << std::endl;
                std::exit(0);
            }
            int check =  std::stoi(argv[2]);
            //checks that the port is in the valid range
            if(check > 65535 || check < 1024){
                std::cout << "invalid arguments" << std::endl;
                std::exit(0);
            }
        }
    }
}
/**
* This function receives a message from the server.
 * @param sock the server's socket number, int type.
 * @param buffer char* type.
 * @param read_bytes int type.
 */
void recvFrom(int sock , char* buffer , int &read_bytes){
    char b [4096] = {0};
    int expected_data_len = sizeof(b);
    // receives message from the server
    read_bytes = recv(sock, b, expected_data_len, 0);
    // checks that the message gets the message correctly
    if(read_bytes < 0){
        perror("error receiving from server");
        std::exit(0);
    }
    strcpy(buffer,b);
}
/**
 * This function is used when the user asks for uploading a file to the server.
 * It opens the file and sends it every row in a message.
 * After the sending it closes the file.
 * @param sock the server's socket number, int type.
 * @param isOpen bool type.
 * @param isFirst bool type.
 * @param isSecond bool type.
 */
void sendFileToServer( int sock, bool &isOpen, bool &isFirst, bool &isSecond) {
    int sent_bytes;
    if(isFirst) {
        char data_addr[4096] = {'1', '\0'};
        int data_len = strlen(data_addr);
        sent_bytes = send(sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            perror("error sending to server");
            std::exit(0);
        }
        isFirst = false;
    }
    std::string input = readByChar(sock);
    std::cout << input << std::endl ;
    std::string temp;
    std::getline(std::cin, temp);
    const char *fName = temp.c_str();
    std::fstream file;
    // opens the asked file
    file.open(fName, std::ios::in);
    // checks if there was a problem during the file's opening
    if (file.fail()) {
        std::cout << "can't open the specified file, please upload new files in order to continue" << std::endl;
        std::string  problem = "problemWithPath";
        // transfer string to char[]
        char data_addr [4096] = {0};
        // copies the string
        for(int i = 0;i < problem.length(); i++) {
            data_addr[i] = problem[i];
        }
        data_addr[problem.length()] = '\n';
        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            perror("error sending to server");
            std::exit(0);
        }
        isOpen = false;
        return;
    }
    std::string line;
    while(getline(file, line)) {
        // transfer string to char[]
        char data_addr [4096] = {0};
        // copies the string
        for(int i = 0;i < line.length(); i++) {
            data_addr[i] = line[i];
        }
        data_addr[line.length()] = '\n';
        int data_len = strlen(data_addr);
        int sent_bytes = send(sock, data_addr, data_len, 0);
        if (sent_bytes < 0) {
            perror("error sending to server");
            std::exit(0);
        }
    }
    char data_addr_temp [7] = "Finish";
    data_addr_temp[6] = '\n';
    sent_bytes = send(sock, data_addr_temp, 7, 0);
    if (sent_bytes < 0) {
        perror("error sending to server");
        std::exit(0);
    }
    file.close();
    // receive from server upload complete
    std::string st = readByChar(sock);
    std::cout << st << std::endl;
    if(isSecond) {
        std::string symbol = "invalid files";
        st = readByChar(sock);
        if(strcmp(st.c_str(), symbol.c_str()) == 0) {
            std::cout << st << std::endl;
        }
    }
    isSecond = true;
}

/**
 * This function is used for asking the server to classify the vectors.
 * @param sock the client's socket number, int type.
 */
void classification(int sock){
    char data_addr[4096] = {'3', '\0'};
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("error sending to server");
        std::exit(0);
    }

    std::string s = readByChar(sock);
    std::cout << s << std::endl;
}
/**
 * This function is used for asking the server for the current parameters, the current k and the current metric type.
 * It prints the current parameters to the the user after getting them from the server and the user can change the
 * parameters to new valid values.
 * @param sock the server's socket number, int type.
 */
void parameters(int sock) {
    char data_addr[4096] = {'2', '\0'};
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("error sending to server");
        std::exit(0);
    }
    // receive from server upload complete
    char buffer[4096] = {0};
    int expected_data_len = sizeof(buffer);
    // receives message from the server
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    // checks that the message gets the message correctly
    if(read_bytes < 0){
        perror("error receiving from server");
        std::exit(0);
    }
    if (read_bytes > 0) {
        // prints the message
        std::cout << buffer << std::endl;
    }
    std::string line;
    getline(std::cin, line);

    //std::cout << line.length() << std::endl;
    if(line.length() == 0) {
        char data_addr_temp [8] = "Finish\n";
        sent_bytes = send(sock, data_addr_temp, 7, 0);
        if (sent_bytes < 0) {
            perror("error sending to server");
            std::exit(0);
        }
    }
    else {
        char data_addr_2 [4096]= {0};
        // copies the string
        for(int i = 0;i < line.length(); i++){
            data_addr_2[i] = line[i];
        }
        data_addr_2[line.length()] = '\n';
        data_len = strlen(data_addr_2);
        sent_bytes = send(sock, data_addr_2, data_len, 0);
        if (sent_bytes < 0) {
            perror("error sending to server");
            std::exit(0);
        }
    }

    bool stopper = false;
    while(!stopper) {
        std::string s = readByChar(sock);
        std::string finish = "-1";
        if(strcmp(s.c_str(), finish.c_str()) != 0) {
            std::cout << s << std::endl;
        }
        else {
            stopper = true;
        }
    }
}

/**
 * This function sends '5' to the server for choosing case 5, and receives back a message from the server if the choose
 * is valid or not.
 * @param sock The server's socket number, int type.
 * @return "-1" if the choose is not valid or the first row to print to the file otherwise.
 */
std::string helpMakeResultFile(int sock){
    char data_addr[4096] = {'5', '\0'};
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("error sending to server");
        std::exit(0);
    }
    std::string status;
    status = readByChar(sock);
    std::string please = "please";
    if(strcmp(status.c_str(), please.c_str()) == 0) {
        std::string s = readByChar(sock);
        std::cout << s << std::endl;
        return "-1";
    }
    return status;
}


/**
 * This function asks the user for a path of a file to print the classification of the vectors.
 * @return The path if the user's input is valid, "-1" otherwise.
 */
std::string getPath(){
    std::string path;
    std::string temp;
    std::cout << "Please enter path for new csv file" << std::endl;
    std::getline(std::cin, path);
//    temp = path + "/result.csv";


//    std::cout << tmep << std::endl;

//    const char *fName = temp.c_str();
    const char *fName = path.c_str();

    std::fstream file;
    file.open(fName, std::ios::out);
    if(file.fail()){
        file.close();
        std::cout << "invalid path\n";
        return "-1";
    }
    return path;
}

/**
 * This function gets from the server the classifications of the test vectors and prints them to the file.
 * @param sock the server's socket number, int type.
 * @param status the first row of the file, string type.
 * @param path the user's file path.
 */
void makeResultFile(int sock , std::string status, std::string path) {
//    path += "/result.csv";
    const char *fName = path.c_str();
    std::fstream file;
    file.open(fName, std::ios::out);
//    std::ofstream file;
//    file.open("result.csv");
    std::string result;
    bool stopper = false;
    bool isFirst = true;
    std::string done = "Done.";
    while(!stopper) {
        if(isFirst){
            if(strcmp(status.c_str(), done.c_str()) == 0) {
                stopper = true;
            }
            else{
                file<<status<<"\n";
            }
            isFirst = false;
        }
        else {
            result = readByChar(sock);
            if (strcmp(result.c_str(), done.c_str()) == 0) {
                stopper = true;
            } else {
                file << result << "\n";
            }
        }
    }
    file.close();
}

/**
 * This function asks the server for the classifications of the vectors and print them to the client's screen.
 * @param sock the server's socket number.
 */
void printPreparedVectors(int sock) {
    //sends the user's choose to server
    char data_addr[4096] = {'4', '\0'};
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("error sending to server");
        std::exit(0);
    }

    std::string result;
    bool stopper = false;
    std::string done = "Done.";
    std::string please = "please";
    while(!stopper) {
        result = readByChar(sock);
        if(strcmp(result.c_str(), please.c_str()) == 0) {
            stopper = true;
            continue;
        }
        std::cout << result << std::endl;
        if(strcmp(result.c_str(), done.c_str()) == 0) {
            stopper = true;
        }
    }
}

/**
 * This function asks the server to close the connection, it sends '8' to the server.
 * @param sock the server's socket number.
 */
void sendClose(int sock) {
    //sends the user's choose to server
    char data_addr[4096] = {'8', '\0'};
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("error sending to server");
        std::exit(0);
    }
}

/**
 * This function reads all the data from the buffer.
 * @param sock
 */
void readForClean(int sock) {
    bool stopper = false;
    std::string done = "Done.";
    while(!stopper) {
        std::string result = readByChar(sock);
        if(strcmp(result.c_str(), done.c_str()) == 0) {
            stopper = true;
        }
    }
}

using namespace std;
/**
 * The main method uses the user's parameters from char** argv and connects to the server according to
 * the parameters. In addition, the user enters vector , distance calculation type and k number.
 * The client sends the information to the server and prints the server's answer.
 * @param argc int array
 * @param argv char** array
 * @return -
 */
int main(int argc, char** argv)
{
    // validation of the user's arguments in the command line
    areArgumentsValid(argv);
    const char *ip_address;
    int temp_port_no;
    try {
         ip_address = argv[1];
         temp_port_no = std::stoi(argv[2]);
    }
    catch (std::exception& e){
        std::cout << "invalid arguments"<< std::endl;
        std::exit(0);
    }
    const int port_no = temp_port_no;
    // creates socket
    int sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock<0)
    {
        perror("error creating socket");
    }
    // creates server socket for the connection.
    struct sockaddr_in sin;
    memset(&sin,0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    // connects to the server
    if (connect(sock,(struct sockaddr*)&sin, sizeof(sin))<0)
    {
        perror("error connecting to server");
        std::exit(0);
    }

    // get menu from server
    char menu[4096] = {0};
    int expected_data_len = sizeof(menu);
    // receives menu from the server
    int read_bytes = recv(sock, menu, expected_data_len, 0);
    if(read_bytes < 0){
        perror("error receiving from server");
        std::exit(0);
    }
    std::string choose;
    bool isDone = false;
    bool isFirst = true;
    bool isSecond = false;
    std::vector <std::thread> threads;
    std::string result;
    std::string check = "-1";
    while(true) {
        std::cout << menu << std::endl;
        std::getline(std::cin, choose);
        if(!isValidInteger(choose)) {
            std::cout << "invalid option\n";
            continue;
        }
        int pick = stoi(choose);
        bool isOpen = true;
        switch(pick) {
            case 1:
                isOpen = true;
                isFirst = true;
                isSecond = false;
                sendFileToServer(sock, isOpen, isFirst, isSecond);
                if(isOpen) {
                    sendFileToServer(sock, isOpen, isFirst, isSecond);
                }
                break;
            case 2:
                parameters(sock);
                break;
            case 3:
                classification(sock);
                break;
            case 4:
                printPreparedVectors(sock);
                break;
            case 5:
                result = helpMakeResultFile(sock);
                if(strcmp(result.c_str(),check.c_str())!= 0){
                    std::string path = getPath();
                    if(strcmp(path.c_str(),check.c_str())!= 0) {
                        threads.emplace_back(std::thread(makeResultFile, sock, result, path));
                    }
                    else {
                        readForClean(sock);
                    }
                }
                break;
            case 8:
                sendClose(sock);
                isDone = true;
                break;
            default:
                std::cout << "invalid option\n";
        }
        if(isDone) {
            break;
        }
    }
    for(int i = 0 ; i < threads.size(); i++){
        threads.at(i).join();
    }
}