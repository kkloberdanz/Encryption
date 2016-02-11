#!/usr/bin/python3

import sys

# input handling
try:
    try:
        if sys.argv[1] == "-f" and sys.argv[2]:
            userInput = open(sys.argv[2], "r")
        else:
            userInput = sys.argv[1:]
    except:
        print("caesarCipher: expecting input file")
        sys.exit()

except:
    print("caesarCipher: no input argument given.")
    sys.exit()

output = ""

for word in userInput:
    for letter in word:

        # if lowercase letter
        if (ord(letter) >= ord("a")) and (ord(letter) <= ord("z")):
            if ord(letter) >= ord("x"):
                # Sets x to a, y to b, z to c
                letter = chr(ord(letter) - 26)
            output += chr(ord(letter) + 3)
        # if uppercase letter
        elif (ord(letter) >= ord("A")) and (ord(letter) <= ord("Z")):
            if ord(letter) >= ord("X"):
                # Sets x to a, y to b, z to c
                letter = chr(ord(letter) - 26)

            output += chr(ord(letter) + 3)
        # if non-letter character
        else:
            output += chr(ord(letter))

print(output, end='')
        
