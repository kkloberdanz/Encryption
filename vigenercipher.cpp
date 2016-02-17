#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

void printHelp(){
    cout << "vigenerecipher INPUTFILE OUTPUTFILE [optional -d]" << endl;
    cout << "   -d to decipher, otherwise enciphers" << endl;
}

bool isLetter(char letter){
    return (((letter >= 'a') && (letter <= 'z')) && 
            ((letter >= 'A') && (letter <= 'Z')) );
}

int main(int argc, char* argv[]){

    /*
     * input handling
     */
    if( (argc > 1) && ((string)argv[1] == "--help" ) ){
        printHelp();
        exit(EXIT_FAILURE);
    } else if( argc < 3 ){
        cout << "vigenerecipher: not enough input arguments" << endl;
        cout << "(Type vigenerecipher --help for usage)" << endl;
        exit(EXIT_FAILURE);
    } else if( argc > 3 ){
        cout << "vigenerecipher: too few input arguments" << endl;
        cout << "(Type vigenerecipher --help for usage)" << endl;
        exit(EXIT_FAILURE);
    }
    char* inputFilename = argv[1]; 

    ifstream inputFile;

    inputFile.open(inputFilename);

    if( !inputFile.is_open() ){
        cout << "vigenerecipher: Could not open file: " << inputFilename 
            << endl;
        exit(EXIT_FAILURE);
    }

    ofstream outputFile;
    char* outputFilename = argv[2];
    outputFile.open(outputFilename);

    string line;
    int i;
    while( getline(inputFile, line) ){
        cout << line << endl;
        for( i = 0; i < line.length(); i++ ){

            /*
             * Preproscessing, remove all non alpha characters, and lowercase
             * all letters
             */
            if( isLetter(line[i]) ){
                // ensure that it is lowercase
                if( line[i] < 'a' ){
                    // 32, the distance from a to A
                    line[i] = line[i] + 32;
                }
            } else {
                line.erase(i);
            }
        }
        cout << "here" << endl;
        outputFile << line;
    }

    return 0;
}
