/*
 * Programmer    : Kyle Kloberdanz
 * Date Created  : 19 Feb 2015
 * Description   : A simplified implementation of the enigma cipher.
 *                 Uses 1 rotor instead of 3
 *
 * Usage:
 *     To encrypt:
 *                : To encipher:
 *                    ./enigma INPUTFILE OUTPUTFILE
 *
 *                Encipher without spaces:
 *                    ./enigma INPUTFILE OUTPUTFILE --no-spaces
 *
 *                To decipher:
 *                    ./enigma INPUTFILE OUTPUTFILE -d
 *
 *                Decipher withoug spaces:
 *                    ./enigma INPUTFILE OUTPUTFILE -d --no-spaces
 *
 * Notes        : Compiled with g++ (Debian 5.3.1-8) (stretch-sid)
 *                and GNU Make 4.1
 *                Complier MUST be compatable with c++11 standard
 *
 *                For best results, compile and run with a linux system
 *                (Not tested for Windows, OSX, or any other OS)
 *
 *                To compile, ensure you are in the same directory as the
 *                Makefile, then type 'make'
 *
 *                To compile without make: 
 *                'g++ enigma.cpp -o Enigma -Wall -Wextra -O2 -std=c++11'
 *              
 *
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <ctime>
#include <vector>
#include <random>
#include <iterator>
#include <algorithm>

using namespace std;

string preproscess(string line, bool noSpaces);

class Rotor{
    private:
        vector<char> shiftRotor;
    public:
        Rotor();
        void printShiftRotor();
        void initialize();
        void initialize(string);
        void shiftRight();
        void shiftLeft();
        string encryptString(string);
        string decipherString(string);
};

Rotor::Rotor(){
}

void Rotor::printShiftRotor(){
    for( vector<char>::iterator it = shiftRotor.begin(); 
                                it != shiftRotor.end(); it++ ){
        //cout << *it << ' ';
        cout << *it;
    }
    cout << endl;
}

void Rotor::initialize(){
    /*
    shiftRotor = {'b','z','e','p','l','w','m','s','y','o','k','n','c','t','g','d','h','x','i','u','j','q','v','r','f','a'};
    int i;
    for( i = 0; i < shiftAmounts; i++ ){
        this->shiftLeft();
    }
    */

    // fills the vector, shiftRotor with the letters a -> z,
    // then randomizes their order
    srand(time(0));
    int i;
    for( i = 'a'; i <= 'z'; i++ ){
        shiftRotor.push_back(i);
    }
    random_shuffle( shiftRotor.begin(), shiftRotor.end() );
    //this->printShiftRotor();
}

void Rotor::initialize(string startingPosition){
    // fills the vector, shiftRotor with the letters from startingPosition
    unsigned int i;
    startingPosition = preproscess(startingPosition, true);
    for( i = 0; i < startingPosition.length(); i++ ){
        shiftRotor.push_back(startingPosition[i]);
    }
}

void Rotor::shiftRight(){
    char tmp = shiftRotor.back();
    shiftRotor.pop_back();
    shiftRotor.insert(shiftRotor.begin(), tmp);
}

void Rotor::shiftLeft(){
    char tmp = shiftRotor.front();
    shiftRotor.erase(shiftRotor.begin());
    shiftRotor.push_back(tmp);
}

string Rotor::encryptString(string str){
    string output = "";
    unsigned int i;
    for( i = 0; i < str.length(); i++ ){
        if( str[i] != ' ' ){
            output += shiftRotor[str[i] - 'a'];
        } else {
            output += ' ';
        }
        this->shiftLeft();
    }
    return output;
}

string Rotor::decipherString(string str){
    string output = "";
    unsigned int i;
    unsigned int j;
    // linear search through shiftRotor for the letter
    // at str[i]. Append the position + 'a' to output
    
    for( i = 0; i < str.length(); i++ ){
        if( str[i] == ' ' ){
            output += ' ';
        } else {
            for( j = 0; j < shiftRotor.size(); j++ ){
                if(shiftRotor[j] == str[i]){
                    output += (j + 'a');
                    break;
                }
            }
        }
        this->shiftLeft();
    }
    return output;
}

bool isLetter(char ch){
    return (((ch >= 'a')&&(ch <= 'z')) || ((ch >= 'A')&&(ch <= 'Z')));
}

string preproscess(string line, bool noSpaces){
    // Preproscessing, remove all non alpha characters, 
    // and lowercase all letters
    string outputline = "";
    unsigned int i;
    for( i = 0; i < line.length(); i++ ){
        if (noSpaces){
            if( (isLetter(line[i])) ){
                if( (line[i] >= 'A') && (line[i] <= 'Z') ){
                    // 32, the distance from a to A
                    line[i] = line[i] + 32;
                }
                outputline += line[i];
            }
        } else {
            if( (isLetter(line[i])) || (line[i] == ' ') ){
                if( (line[i] >= 'A') && (line[i] <= 'Z') ){
                    // 32, the distance from a to A
                    line[i] = line[i] + 32;
                }
                outputline += line[i];
            }
        }
    }
    return outputline;
}

void printHelp(){
    cout << "Usage: To encipher:\n"
            "        ./enigma INPUTFILE OUTPUTFILE\n\n"
 
            "Encipher without spaces:\n"
            "        ./enigma INPUTFILE OUTPUTFILE --no-spaces\n\n"

            "   To decipher:\n"
            "       ./enigma INPUTFILE OUTPUTFILE -d\n\n"

            "   Decipher withoug spaces:\n\n"
            "       ./enigma INPUTFILE OUTPUTFILE -d --no-spaces\n"
 << endl;
}

int main(int argc, char* argv[]){

    /*
     * input handling
     */
    Rotor rotor1;
    //string startingPosition = "pnvqtaeuxclkwgiohmbjfdrszy";

    bool setDecrypt = false;
    bool noSpaces   = false;
    if( (argc > 1) && ((string)argv[1] == "--help" ) ){
        printHelp();
        exit(EXIT_FAILURE);

    } else if( (argc == 4) && ((string)argv[3] == "-d") ){
        setDecrypt = true;

    } else if ( (argc == 4) && ((string)argv[3] == "--no-spaces") ) {
        noSpaces = true;

    } else if ( (argc == 5) && ((string)argv[3] == "-d") 
                            && ((string)argv[4] == "--no-spaces")){
        setDecrypt = true;
        noSpaces = true;

    } else if( argc < 3 ){
        cout << "enigma: not enough input arguments" << endl;
        cout << "(Type enigma --help for usage)" << endl;
        exit(EXIT_FAILURE);

    } else if( argc > 3 ){
        cout << "enigma: too many input arguments" << endl;
        cout << "(Type enigma --help for usage)" << endl;
        exit(EXIT_FAILURE);
    }
    char* inputFilename = argv[1]; 

    ifstream inputFile;

    inputFile.open(inputFilename);

    if( !inputFile.is_open() ){
        cout << "enigma: Could not open file: " << inputFilename << endl;
        exit(EXIT_FAILURE);
    }

    ofstream outputFile;
    char* outputFilename = argv[2];

    outputFile.open(outputFilename);

    string line;
    string plainText = "";
    string keyString = "";
    string cipherText = "";
    string decipheredText = "";

    /*
    cout << (setDecrypt? "Enter key to decrypt: " :
                         "Enter key to encrypt: ");
    cin >> key;
    */
    string key;
    if( setDecrypt ){
        cout << "Enter key to decrypt: ";
        getline(cin, key);

        if(key.length() != 26){
            cout << "Key is not the correct length!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    if( setDecrypt ){
        rotor1.initialize(key);
        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            cipherText = preproscess(line, noSpaces); 
            decipheredText = rotor1.decipherString(cipherText);
            outputFile << decipheredText << endl;
        }

    } else {
        rotor1.initialize();
        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            plainText  = preproscess(line, noSpaces);
            cipherText = rotor1.encryptString(plainText); 
            outputFile << cipherText << endl;
        }
    }

    outputFile.close();
    inputFile.close();
    return 0;
}
