/**
 \file hangman.h
*/
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#define BUF_SIZE 256 // this is the Buffer size.

int gameMode(); // the function which let the user choose the game mode
void upperCase(char *toTransform); // to make upper case letter from the user input.
char *readWord(char *filePath); // filepath function reads a given file and selects a word randomly.

#endif
