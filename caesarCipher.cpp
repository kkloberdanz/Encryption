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

    ifstream inputFile;

    /*
     * Input file handeling
     */
    bool setDecode;
    if( (argc >= 3) && ( (string)argv[1] == "-f") ){
        inputFile.open(argv[2]);
        if( (argc == 4) && ( (string)argv[3] == "-d") ){
            setDecode = true;
        }

    } else {
        cout << "caesarCipher: usage -- ciphter -f FILENAME" << endl;
        exit(EXIT_FAILURE);
    }

    if( !inputFile.is_open() ){
        cout << "caesarCipher: ERROR, input file did not open properly" 
            << endl;
        exit(EXIT_FAILURE);
    }

    /*
     * Encryption begins here
     */
    string line;
    int i;
    //char letter;
    while( getline(inputFile, line) ){

        // encode
        if( !setDecode ){
            for( i = 0; i < line.length(); i++ ){
                if( isLetter(line[i]) ){
                    line[i] += SHIFTAMOUNT;
                }
            }
            cout << line << endl;

        // decode
        } else {
            for( i = 0; i < line.length(); i++ ){
                if( isLetter(line[i]) ){
                    line[i] -= SHIFTAMOUNT;
                }
            }
            cout << line << endl;
        }
    }

    inputFile.close();
    return 0;
}

bool isLetter(char ch){
    return ((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z'));
}
