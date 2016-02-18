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

class Rotor{
    private:
        vector<char> alphabet;
    public:
        Rotor();
        void initialize();
        void shift();
        string encryptString(string);
};

Rotor::Rotor(){
}

void Rotor::initialize(){
    srand(time(0));
    int i;
    for( i = 'a'; i <= 'z'; i++ ){
        alphabet.push_back(i);
    }
    random_shuffle( alphabet.begin(), alphabet.end() );

    // for testing, prints vector
    /*
    for( vector<char>::iterator it = alphabet.begin(); it != alphabet.end(); it++ ){
        cout << ' ' << *it;
    }
    cout << endl;
    */
}

void Rotor::shift(){
    char tmp = alphabet.back();
    alphabet.pop_back();
    alphabet.insert(alphabet.begin(), tmp);
    // for testing, prints vector
    /*
    for( vector<char>::iterator it = alphabet.begin(); it != alphabet.end(); it++ ){
        cout << ' ' << *it;
    }
    cout << endl;
    */
}

string Rotor::encryptString(string str){
    string output = "";
    unsigned int i;
    for( i = 0; i < str.length(); i++ ){
        output += alphabet[str[i] - 'a'];
        this->shift();
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

int main(int argc, char* argv[]){

    /*
     * input handling
     */
    Rotor rotor1;
    rotor1.initialize();

    bool setDecrypt = false;
    bool noSpaces   = false;
    if( (argc > 1) && ((string)argv[1] == "--help" ) ){
        //printHelp();
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
        cout << "enigma: Could not open file: " << inputFilename 
            << endl;
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

    // Delete before submittion
    /*
    ofstream testFile;
    testFile.open("test.txt");
    */

    if( setDecrypt ){
        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            cipherText = preproscess(line, noSpaces); 
            outputFile << decipheredText << endl;
        }

    } else {

        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            plainText  = preproscess(line, noSpaces);
            //testFile << plainText << endl;

            cipherText = rotor1.encryptString(plainText); 
            outputFile << cipherText << endl;
        }
    }

    outputFile.close();
    inputFile.close();
    testFile.close();
    return 0;
}
