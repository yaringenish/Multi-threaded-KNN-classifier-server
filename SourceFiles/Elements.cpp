//
// Created by yarin on 12/01/2023.
//

#include "Elements.h"
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
 * This method is the constructor of the Elements class.
 * It initializes the the class members.
 */
Elements::Elements() {
    this->distType = "AUC";
    this->k = 5;
    this->isUpload = true;
}

/**
 * This method is the destructor of the Elements class.
 */
Elements::~Elements(){}


/**
 * This is a setter method to set the maxK member. It represents the number of the rows in the
 * train vectors file.
 * @param maxK int type.
 */
void Elements::setMaxK(int maxK) {
    this->maxK = maxK;
}

/**
 * This is a setter method to set the fv member.
 * @param fv FileValidate* type.
 */
void Elements::setFile(FileValidate* fv) {
    this->fv = fv;
}

/**
 * This is a method to set the k member of the class.
 * @param k int type.
 */
void Elements::setK(int k) {
    this->k = k;
}

/**
 * This is a setter method to set the distType.
 * @param distType string type.
 */
void Elements::setDistType(std::string distType){
    this->distType = distType;
}

/**
 * This is a setter method to set the classifiedVectors.
 * @param classifiedVectors std::vector <std::pair<int, std::string>>* type.
 */
void Elements::setClassifiedVectors(std::vector <std::pair<int, std::string>> *classifiedVectors) {
    this->classifiedVectors = classifiedVectors;
}

/**
 * This is a getter method to get the fv member.
 * @return FileValidate* type.
 */
FileValidate* Elements::getFv() {
    return this->fv;
}

/**
 * This is a getter method to get the current k.
 * @return int type.
 */
int Elements::getK(){
    return this->k;
}

/**
 * This is getter method to get the maxK
 * @return int type.
 */
int Elements::getMaxK(){
    return this->maxK;
}

/**
 * This is a getter method to get the current distType.
 * @return distType string type.
 */
std::string Elements::getDistType() {
    return this->distType;
}
/**
 * This is a getter method to get the ClassifiedVectors.
 * @return classifiedVectors member, std:: vector<std::pair< int,std::string>>* type.
 */
std:: vector<std::pair< int,std::string>>* Elements::getClassifiedVectors() {
    return this->classifiedVectors;
}

/**
 * This is a setter method to set the isUpload member.
 * @param val , bool type.
 */
void Elements::setIsUpload(bool val) {
    this->isUpload = val;
}

/**
 * This is a getter method to get the isUpload member.
 * @return isUpload, bool type.
 */
bool Elements::getIsUpload() {
    return this->isUpload;
}



;