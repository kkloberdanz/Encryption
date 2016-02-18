/*
 * Programmer   : Kyle Kloberdanz
 * Date Created : 17 Feb 2016
 *
 * Description  : Reads an input file (specified from command line)
 *                and creates an output file (specified from command line)
 *                with the encrypted text
 *
 * Usage        : To encipher:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE
 *
 *                Encipher without spaces:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE --no-spaces
 *
 *                To decipher:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE -d
 *
 *                Decipher withoug spaces:
 *                    ./vigenerecipher INPUTFILE OUTPUTFILE -d --no-spaces
 *
 * Notes        : Compiled with g++ (Debian 5.3.1-8)
 *                For best results, compile and run with a linux system
 *                (Not tested for Windows, OSX, or any other OS)
 *              
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cassert>

using namespace std;

void printHelp(){
    cout << "Usage: To encipher:\n"
            "        ./vigenerecipher INPUTFILE OUTPUTFILE\n\n"
 
            "Encipher without spaces:\n"
            "        ./vigenerecipher INPUTFILE OUTPUTFILE --no-spaces\n\n"

            "   To decipher:\n"
            "       ./vigenerecipher INPUTFILE OUTPUTFILE -d\n\n"

            "   Decipher withoug spaces:\n\n"
            "       ./vigenerecipher INPUTFILE OUTPUTFILE -d --no-spaces\n"
 << endl;
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

string generateKeyString(string key, int size){
    int i;
    string outputString = "";
    for( i = 0; i < size; i++ ){
        outputString += key[i%key.length()];
    }
    return outputString;
}

string applyCipher(string plainText, string keyString){

    assert( plainText.length() == keyString.length() );

    string cipherText = "";
    unsigned int i;
    char mi;
    char ki;
    for( i = 0; i < plainText.length(); i++ ){
        mi = plainText[i] - 'a';
        ki = keyString[i] - 'a';
        if( plainText[i] != ' ' ){
            cipherText += ((mi + ki + 26) % 26) + 'a';
        } else {
            cipherText += plainText[i];
        }
    }
    return cipherText;
}

string decipher(string cipherText, string keyString){

    assert( cipherText.length() == keyString.length() );

    string plainText = "";
    unsigned int i;
    char ci;
    char ki;
    for( i = 0; i < cipherText.length(); i++ ){
        ci = cipherText[i] - 'a';
        ki = keyString [i] - 'a';
        if( cipherText[i] != ' ' ){
            plainText += ((ci - ki + 26) % 26) + 'a';
        } else {
            plainText += cipherText[i];
        }
    }
    return plainText;
}

int main(int argc, char* argv[]){

    /*
     * input handling
     */
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

    // key will be used to encrypt the text
    string key = "";
    cout << (setDecrypt? "Enter key to decrypt: " :
                         "Enter key to encrypt: ");
    cin >> key;

    string line;
    string plainText = "";
    string keyString = "";
    string cipherText = "";
    string decipheredText = "";

    if( setDecrypt ){
        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            cipherText = preproscess(line, noSpaces);

            // makes a string of the key repeated for the length of line
            keyString  = generateKeyString(key, cipherText.length());

            // decipher text
            decipheredText = decipher(cipherText, keyString);

            outputFile << decipheredText << endl;
        }

    } else {

        while( getline(inputFile, line) ){
            // remove non-alpha characters and lowercase all letters
            plainText  = preproscess(line, noSpaces);

            // makes a string of the key repeated for the length of line
            keyString  = generateKeyString(key, plainText.length());

            // apply cipher to line
            cipherText = applyCipher(plainText, keyString);

            outputFile << cipherText << endl;
        }
    }

    outputFile.close();
    inputFile.close();
    return 0;
}
