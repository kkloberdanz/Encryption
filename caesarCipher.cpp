#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

bool isLetter(char);

int main(int argc, char* argv[]){

    const int SHIFTAMOUNT = 3;

    /*
     * Input file handeling
     */
    if ( argc > 5 ){
        cout << "caesarCipher: Too many input arguments" << endl;
        exit(EXIT_FAILURE);
    } else if( argc < 2 ){
        cout << "caesarCipher: Too few input arguments" << endl;
        exit(EXIT_FAILURE);
    }

    unsigned int i;
    unsigned int j;
    int modifier;
    ifstream inputFile;

    bool setDecode    = false;
    bool readFromFile = true;
    for( i = 0; i <= argc; i++ ){
        // find modifiers in argv
        if( argv[i][0] == '-' ){
            // set modifier accordingly
            for( j = 1; argv[i][j] != '\0'; j++ ){
                //cout << argv[i][j];
                modifier = argv[i][j];
                //cout << "modifier == " << modifier << endl;

                switch (modifier){
                    case 'o':
                        //cout << "caesarCipher: Specify output file AFTER "
                         //   "the input file" << endl;
                        exit(EXIT_FAILURE);
                        break;
                    case 'f':
                        // specifiy input file
                        readFromFile = true;
                        inputFile.open(argv[i+1]);
                        cout << "Opening file" << endl;
                        break;
                    case 'd':
                        setDecode = true;
                        //cout << "Decoding" << endl;
                        break;
                    default:
                        //cout << "caesarCipher: Specify input file with -f" 
                            //<< endl;
                        exit(EXIT_FAILURE);
                }
            }
            break; // exit outer for loop
        }
    }

    std::ofstream outputFile;
    bool printToFile = false;
    if( argc == 5){
        if( (string)argv[3] == "-o" ){
            printToFile = true;
            outputFile.open(argv[4]);
        }
    } 

    if( !inputFile.is_open() ){
        cout << "caesarCipher: ERROR, INPUT file did not open properly" 
            << endl;
        exit(EXIT_FAILURE);
    }

    if( printToFile && !outputFile.is_open() ){
        cout << "caesarCipher: ERROR, OUTPUT file did not open properly" 
            << endl;
    }

    /*
     * Encryption begins here
     */
    string line;
    //char letter;
    if( readFromFile ){
        while( getline(inputFile, line) ){

            // encode
            if( !setDecode ){
                for( i = 0; i < line.length(); i++ ){
                    if( isLetter(line[i]) ){
                        line[i] += SHIFTAMOUNT;
                    }
                }
                if( !printToFile ){
                    // then print to stdout
                    cout << line << endl;
                } else {
                    outputFile << line;
                }

            // decode
            } else {
                for( i = 0; i < line.length(); i++ ){
                    if( isLetter(line[i]) ){
                        line[i] -= SHIFTAMOUNT;
                    }
                }
                if( !printToFile ){
                    // then print to stdout
                    cout << line << endl;
                } else {
                    outputFile << line;
                }
            }
        }
    } else {
        // read from stdin
        // TODO: Not yet working
        line = argv[1];
        cout << line << endl;
    }

    inputFile.close();
    outputFile.close();
    return 0;
}

bool isLetter(char ch){
    return ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'));
}
