//
// Created by Roi on 11/01/2023.
//
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
#include "Parameters.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Elements.h"

/**
 * constructor method to initiate the Parameters class.
 * @param dio  DefaultIO* type.
 */
Parameters::Parameters(DefaultIO* dio) {
    this->dio = dio;
    std:: string s = "The current KNN parameters are: K = 5, distance metric = AUC";
    this->description = s;
    this->isMetricValid = true;
    this->isKValid = true;
    this->k = 5;
    this->dstType = "AUC";
}

/**
 * This function splits the client's input for k and metric and checks that they are valid.
 * it checks that the input for k is an integer anf the input gor metric is one of the five options.
 * @param str the user's full input.
 * @param k int type.
 * @param dstType string type.
 * @param isKValid an indicator if the k is valid.
 * @param isMetricValid an indicator if the metric is valid.
 * @param elements Elements* type.
 * @return true if the user's input is valid, else otherwise.
 */
bool Parameters::fromString(std::string str, int &k, std::string &dstType, bool &isKValid, bool &isMetricValid, Elements* elements) {
    std::stringstream src(str);
    std::string temp;
    // extract k from the string
    std::getline(src, temp, ' ');
    this->isKValid = true;
    for(int i = 0; i < temp.size(); i++) {
        if(! std::isdigit(temp[i])) {
            this->isKValid = false;
        }
    }
    int num;
    if(this->isKValid) {
        num = std::stoi(temp);
    }
    if(elements->getMaxK() < num){
        this->isKValid = false;
//        std::cout << "yarin king" << std::endl;
    }
    //extract dstType from string
    std::string tempDest;
    std::getline(src, temp, ' ');
    if(std::strcmp(temp.c_str(), "AUC") == 0) {
        tempDest = "AUC";
        this->isMetricValid = true;
    }
    else if(std::strcmp(temp.c_str(), "MAN") == 0) {
        tempDest = "MAN";
        this->isMetricValid = true;
    }
    else if(std::strcmp(temp.c_str(), "CHB") == 0) {
        tempDest = "CHB";
        this->isMetricValid = true;
    }
    else if(std::strcmp(temp.c_str(), "CAN") == 0) {
        tempDest = "CAN";
        this->isMetricValid = true;
    }
    else if(std::strcmp(temp.c_str(), "MIN") == 0) {
        tempDest = "MIN";
        this->isMetricValid = true;
    }
    else{
        this->isMetricValid = false;
    }
    if(this->isKValid && this->isMetricValid) {
        k = num;
        dstType = tempDest;
        elements->setDistType(this->getDestType());
        elements->setK(this->getK());
        return true;
    }
    else{
        return false;
    }

}

/**
 * This method gets from the client the user's input and checks that the input is valid using fromString method.
 * If the input is valid it changes the current k and metric to the new values, else it doesn't change the k
 * and metric and sends the client what was the problem.
 * @param elements Elements* type.
 */
void Parameters::execute(Elements* elements) {
    this->isKValid = true;
    this->isMetricValid = true;
    // writes to the client the current k and dstType
    std::string strK = std::to_string(this->k);
    std:: string result = "The current parameters are: k = " + strK +", distance metric = " + this->dstType;

    //std::cout << result << std::endl;

    this->dio->write(result);
    std::string s = this->dio->readByChar();


    std::string finish = "Finish";
    if(strcmp(s.c_str(), finish.c_str()) != 0) {
        bool split = fromString(s, this->k, this->dstType, this->isKValid, this->isMetricValid, elements);
        if (!this->isKValid && this->isMetricValid) {
            std::string s = "invalid value for k\n";
            this->dio->write(s);
        }
        if (!this->isMetricValid && this->isKValid) {
            std::string s = "invalid value for metric\n";
            this->dio->write(s);
        }
        if (!this->isKValid && !this->isMetricValid){
            std::string s = "invalid value for k\ninvalid value for metric\n";
            this->dio->write(s);
        }
    }
    std::string fin = "-1\n";
    this->dio->write(fin);

}

/**
 * This is a getter method to get the k member.
 * @return current k, int type.
 */
int Parameters::getK() {
    return this->k;
}

/**
 * This is a getter method to get the current destType member.
 * @return the current destType, string type.
 */
std::string Parameters::getDestType() {
    return this->dstType;
}

/**
 * destructor method for Parameters class.
 */
Parameters::~Parameters(){}