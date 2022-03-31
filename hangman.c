/**
 * @author MS
 * @file hangman.c
 * @brief prompts the user to choose the game mode, or to quit the game!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>
#include <sys/unistd.h>
#include <windows.h>
#include "hangman.h"
#include "functions.h"

/// \brief this function comes after the main function, it let the user choose the game mode
/// \brief this function comes next after main, which allows the user to choose the preferred game mode
int gameMode() {

    printf("--------------------------------------------\n");
    printf("| #  #   #   #   #  #### #   #   #   #   # |\n");
    printf("| #  #  # #  ##  # #     ## ##  # #  ##  # |\n");
    printf("| #### ##### # # # #  ## # # # ##### # # # |\n");
    printf("| #  # #   # #  ## #   # #   # #   # #  ## |\n");
    printf("| #  # #   # #   #  ###  #   # #   # #   # |\n");
    printf("--------------------------------------------\n\n");
    printf("\tWhich mode do you prefer ? \n\t -> r : Random word \n\t -> f : From file \n\t -> h : Help \n\t -> q : Quit \n\t ");
    // Prints the welcome statement

    char ch;
    printf("\n\tInput :\n");
    ch = getchar();

    switch (ch) {
        // ch for switch case depending on user's choice
        // r for random word
        // f get the word from a file
        // h if the user wants a help
        case 'r':

            printf("\nRandom Word...\n\n");
            sleep(2);
            char filepath[BUF_SIZE] = "C:/Users/asus/Desktop/t.zip/wordlist.txt";
            // location file address
            char* word = readWord(filepath);
            guessingFunc(word);
            free(word);
            getchar();
            gameMode();

        case 'f':
            //brief f gets a word from a file
            printf("\nEnter a valid file path & press ENTER.\n\n");
            Beep(400,500);
            //brief this function gives a sound with 400Hz and 500 m.second
            char c  = 0;
            fgets(&c, BUF_SIZE, stdin);
            //  gets an input from the keyboard
            char userInput[BUF_SIZE + 1];
            fgets(userInput, BUF_SIZE, stdin);
            char* randomWord = readWord(userInput);
            // chooses a random word from the address the user has given
            // userInput the address to be given
            guessingFunc(randomWord);
            free(randomWord);
            //brief clears the word memory after the round has finished
            gameMode();
            // returns to the main menu
        case'h':
            printf("\n\n\n\t\t INSTRUCTIONS \n\n\n\t\t ============");
            printf("\n   1: HANGMAN IS THE GAME WHERE YOU HAVE TO GUESS THE WORD.\n");
            printf("\n   2: YOU WILL HAVE TO GUESS THE RIGHT CHARACTERS.\n");
            printf("\n   3: YOU HAVE THE (n) TRIES, OR THE HANGING PLATFORM WILL BE WAITING:)\n\n\n");
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf("  |  \\|/\n");
            printf("  |    | \n");
            printf("  |   / \\\n");
            printf("__|_________\n\n");
            sleep(10);
            gameMode();

        case 'q':
            printf("\nHave a nice day! :)\n");
            sleep(4);
            return 0;

        default:
        printf("\n\nUnknown error 404 %d\n\n", ch);
        gameMode();
        // return to the main menu

    }
}

    ///\brief This function transforms a passed parameter making it uppercase.
    ///\param toTransform the words with UPPERCASE characters
    void upperCase(char* toTransform) {
    for(int i = 0; toTransform[i]; i++) {
        toTransform[i] = toupper(toTransform[i]);
            }
    }
    //Reads the word to be guessed from a supplied filepath

    ///\brief This function reads a given file and selects a word randomly.
    /// \param filePath the file location.
    ///\return Returns word buffer
    char* readWord(char* filePath) {
    if(filePath == NULL) {
        // if the path is invalid, there will be an error
        fprintf(stderr, "Failure! Invalid filepath.\n");

        printf("error code: %d\n", errno);
        printf("the error message is: %s\n", strerror(errno));
        return NULL;
    }

    if(strchr(filePath, '\n') != NULL) {
    //Checks whether the filepath contains newline characters
        strtok(filePath, "\n");
        // Separates the filepath from other lines
    }

    FILE* fp = fopen(filePath, "r");
    // to see if the file can be opened

    if(fp == NULL) {
        // Checks for errors in the file opening process
        fprintf(stderr, "Fail. Could not open file %s: %s.\n", filePath, strerror(errno)); // raises failure when trying to open the file
        printf("error code: %d\n", errno);
        printf("the error message is : %s\n", strerror(errno));
        return NULL;
    }

    int lineCount = 0; // lineCount  Counts how many lines the file contains
    int randWord; // randWord gets a random number
    char getC; // To read the word character by character


    while(!feof(fp)) {
        //   Reads the file line after line and calculate the line count
        getC = fgetc(fp);
        if(getC == '\n') {
            lineCount++; //increases the line count

        }
    }
    // checking for lines in the file
    if(lineCount == 0) { //if number of lines = 0

        fprintf(stderr, "Error.\n");
        printf("value of errno: %d\n", errno);// prints the code of the error code
        printf("Error code %s\n", strerror(errno));
        perror("message from perror");
        return NULL;
    }
    srand(time(NULL));// generates a random number based in the time seed
    randWord = rand() % lineCount; // Limits the random generator to the lines of the file

    rewind(fp); // to go to the start of the file
    while(randWord > 0 && !feof(fp)) {
        getC = fgetc(fp);//reads the randomly selected word letter by letter
        if(getC == '\n') {
            lineCount--;
            randWord--;
        }
    }

    char* word = malloc(BUF_SIZE); // Allocates the size for the word buffer
        // we should check for error in the memory allocation process
    if(word == NULL) {
        fprintf(stderr, "Error while allocating memory.\n");
        printf("errno: %d\n", errno);// if there is an error in allocating the memory
        printf("Error code : %s\n", strerror(errno));
        perror("perror alert");
        return NULL;
    }

    memset(word, '\0', BUF_SIZE +1); // Initializes the string with NULLs to avoid some errors
    fgets(word, BUF_SIZE , fp); // gets the word and store in the word buffer
    fclose(fp); // Closes the file

    upperCase(word); // start the upperCase function

    return word;
    }
