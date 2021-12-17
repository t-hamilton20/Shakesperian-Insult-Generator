//header file
//Tom Hamilton 20165886
//CMPE/CISC 320 - Assignment 1

#ifndef ASSIGNMENT_1___SHAKESPERIAN_INSULT_GENERATOR_INSULTGENERATOR_18TJWH_H
#define ASSIGNMENT_1___SHAKESPERIAN_INSULT_GENERATOR_INSULTGENERATOR_18TJWH_H

#endif //ASSIGNMENT_1___SHAKESPERIAN_INSULT_GENERATOR_INSULTGENERATOR_18TJWH_H

#pragma once

#include <string>
#include <vector>
using namespace std;

class InsultGenerator {

public:
    struct columns{ //struct used for the three columns in the text file
        vector<string> column1;
        vector<string> column2;
        vector<string> column3;
    };
    InsultGenerator(); //constructor
    columns initialize() const;	//reads in the file and saves the three column into a columns struct and returns the struct
    columns insultColumns = initialize();
    string talkToMe(); //talk to me function that outputs a random insult
    vector<string> generate(int quantity);  //generate function that outputs quantity number of random insults
    void generateAndSave(string filename, int quantity); //generate and save function that accepts a filename and the quantity of insults as parameters
private:
    string filename;
};

class FileException {
public:
    FileException(const string& message);
    string& what();
private:
    string message;
};

class NumInsultsOutOfBounds {
public:
    NumInsultsOutOfBounds(const string& message);
    string& what();
private:
    string message;
};
