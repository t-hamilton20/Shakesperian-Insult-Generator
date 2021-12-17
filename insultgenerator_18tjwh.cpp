//Tom Hamilton - 18tjwh - 20165886
//CMPE/CISC 320 - Assignment 1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "insultgenerator_18tjwh.h"
#include <stdlib.h>
#include <sstream>
#include <set>
#include <time.h>

using namespace std;

int main() {
    InsultGenerator ig;
    vector<string> insults;
    clock_t start=0, finish=0;

    // The initialize() method should load all the source phrases from the InsultsSource.txt file into the attributes.
    // If the file cannot be read, the method should throw an exception.
    try {
        ig.initialize();
    } catch (FileException& e) {
        cerr << e.what() << endl;
        return 1;
    }

    // talkToMe() returns a single insult, generated at random.
    cout << "A single insult:" << endl;
    cout << ig.talkToMe() << endl;

    // Check number to generate limits.
    try {
        insults = ig.generate(-100);
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }
    try {
        insults = ig.generate(40000);
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }

    // generate() generates the requested number of unique insults.
    cout << "\n100 insults, all different:" << endl;
    insults = ig.generate(100);
    if (insults.size() > 0)
        for (int i = 0; i < 100; i++)
            cout << insults[i] << endl;
    else
        cerr << "Insults could not be generated!" << endl;

    // generateAndSave() generates the requested number of unique insults and saves them to the filename
    // supplied.  If the file cannot be written, the method should throw an exception.  Note that the
    // insults in the file should be in alphabetical order!
    // Check the number to generate limits first:
    try {
        ig.generateAndSave("Nothing.txt", 40000);
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }
    cout << "\nSaving 1000 unique insults to a file...";
    try {
        ig.generateAndSave("SavedInsults.txt", 1000);
    } catch (FileException& e) {
        cerr << e.what() << endl;
        return 1;
    }
    cout << "done." << endl;

    // Test ability to generate the maximum number of insults and how long it takes.
    try {
        start = clock();
        insults = ig.generate(10000);
        finish = clock();
    } catch (NumInsultsOutOfBounds& e) {
        cerr << e.what() << endl;
    }
    cout << "\n" << insults.size() << " insults generated." << endl;
    cout << (1e3 * (finish - start)/CLOCKS_PER_SEC) << " msec to complete." << endl;

    return 0;

}

InsultGenerator::InsultGenerator() {}; //constructor

InsultGenerator::columns InsultGenerator::initialize() const {
    //read in the insults text file
    ifstream fileIn("C:\\Users\\tommy\\Documents\\3rd Year\\CMPE 320\\workspace\\Assignment 1 - Shakesperian Insult Generator\\InsultsSource.txt");

    columns columnsInput;  //initialize columns struct to be returned later
    string line, word;
    int count = 1; //count variable used to separate columns
    istringstream iss; //string stream used to separate the columns
    srand(time(0)); //get the random seed

    if (fileIn.fail()) {
        throw FileException("File cannot be read\n"); //throws exception if file cannot be read
    }

    while (!fileIn.eof()){ //goes until end of file
        getline(fileIn, line);
        iss.clear(); //clear iss
        iss.str(line);
        while (iss.good()){
          iss >> word;
          if(count % 3 == 1){ //every third word gets pushed to the column1 vector in the columns struct
              columnsInput.column1.push_back(word);
          }
          else if(count % 3 == 2){ //every third word gets pushed to the column2 vector in the columns struct
                columnsInput.column2.push_back(word);
            }
          else{columnsInput.column3.push_back(word);} //every third word gets pushed to the column3 vector in the columns struct
          count++;
        }
    }

    fileIn.close(); //close file
    return columnsInput; //return full columns
}

string InsultGenerator::talkToMe(){
    //create random numbers between 0 and 49 to generate insults, one for each column
    int n1 = rand() % 50;
    int n2 = rand() % 50;
    int n3 = rand() % 50;
    return "Thou " +insultColumns.column1[n1] + " " + insultColumns.column2[n2] + " " +insultColumns.column3[n3] +"!";
};

vector<string> InsultGenerator::generate(int quantity) {
    if(quantity < 1 || quantity > 10000){
        throw NumInsultsOutOfBounds("Quantity must be between 1 and 10,000\n"); //throws exception if quantity is out of range
    }

    vector<string> temp(quantity); //create a vector of size quantity

    set<string> insults; //create a set to hold the insults
    for (int i = 0; i < quantity; i = insults.size()){ //loop until the set has quantity number of insults
        //generate random numbers
        int n1 = rand() % 50;
        int n2 = rand() % 50;
        int n3 = rand() % 50;

        //insert insult into the set, note that since a set requires every key to be unique, this automatically checks for duplicates
        insults.insert("Thou " + insultColumns.column1[n1] + " " + insultColumns.column2[n2] + " " + insultColumns.column3[n3] + "!");
    }
    copy(insults.begin(), insults.end(), temp.begin()); //copy the set into the vector using the copy function
    return temp;
}

void InsultGenerator::generateAndSave(string filename, int quantity) {
    if(quantity < 1 || quantity > 10000){
        throw NumInsultsOutOfBounds("Quantity must be between 1 and 10,000");
        return;
    }

    ofstream fileOut(filename);
    if (fileOut.fail()) {
        FileException("Error, unable to open file.");
        return;
    }

    set<string> insults; //create a set to hold the insults

    for (int i = 0; i < quantity; i = insults.size()){ //loop until the set has quantity number of insults
        //create random numbers
        int n1 = rand() % 50;
        int n2 = rand() % 50;
        int n3 = rand() % 50;

        //insert insult into the set, note that since a set requires every key to be unique, this automatically checks for duplicates
        insults.insert("Thou " + insultColumns.column1[n1] + " " + insultColumns.column2[n2] + " " + insultColumns.column3[n3] + "!");
    }

    for (auto i = insults.begin(); i != insults.end(); i++) //iterate through the set
    {
        fileOut << *i << endl; //output the set to the file
    }

}

FileException::FileException(const string& message) : message(message) {}
string& FileException::what() { return message; }

NumInsultsOutOfBounds::NumInsultsOutOfBounds(const string& message): message(message) {}
string & NumInsultsOutOfBounds::what() {return message;};