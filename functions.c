
/*! @file functions.c
*@brief this is  the function for the main game
*
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <windows.h>
#include "functions.h"

/*void mercy(int* lives,char d){

    printf("Do you want extra 5 lives?");
    scanf("%c", &d);
    if (d == 'Y' || 'y'){
        lives  +5;

        }

    } */

///\brief this function will run after gameMode function, here will the guessingFunc function  processed
///@param word the word to be guessed
void guessingFunc(char* word) {
    FILE* log; // pointer to a file
    log = fopen("C:/Users/asus/Desktop/t.zip/progress.log","a+");// file This is the path where the log file is created and accessed. The results will be appended to the file.*/
    time_t timeStamp; // Saves what the "time()"-function gets during runtime
    char userInput;
    char* tmpBuff = strdup(word);
    int length = 0;
    int tries = 0;
    int guesses = 0;

 //Determines how long the word is and saves it in the specified variable
    for (int i = 0; word[i] != '\n' ; i++) {
        if (word[i] == '\r') {
            break;
        }
        length++;
        tries++;
        }
    //The chances are equal to the word length
    printf("the random word has been chosen, it has %d characters.\nNow try to guess it...\n",
           length);// tells the user the word is ready.
    /*
     *  this function will save the time from the system and write in it in the log file.
     * This code will be repeated a couple of times below.
     */
    time(&timeStamp);
    fprintf(log,"The show started at: %s\n", ctime(&timeStamp));
    // the beginning of the game

    /*
     *This is where the guessingFunc takes place. It also scans the input and checks whether the input is valid or not
     */
    while (tries > 0 && guesses < length && (userInput = toupper(fgetc(stdin))) != EOF) {
         // Checks for newlines (ENTER-presses in this case)
        if (userInput == '\n') {
            continue;
        }

        time(&timeStamp);
        fprintf(log, "The user tried character '%c' on %s\n", userInput, ctime(&timeStamp));

        if (userInput < 65 || (userInput > 90 && userInput < 97) || userInput > 122) { // brief the user can give characters between A and Z, A is 65 in ASCII , Z is 90 ASCII format
            //   if the user gave other character which not included between A and Z || a and z , there will be an error message
            printf("\nNot valid!\n");
            // error message
            continue;
        }

        int tmpGuessed = guesses;
        /* temporarily saves the old guesses variable.
        *
         * here we should modify the copy of the word so the progress can be tracked. Eg: 'hi' is the word --> 'h' is guessed --> modification takes place: '#i'.
         */
        for (int i = 0; tmpBuff[i] != '\0'; i++) {
        // Increases the "guesses" variable if the user has guessed the word right
            if (tmpBuff[i] == userInput) {
                tmpBuff[i] = '*';
                guesses++;
            }
        }
        /*
         * This is interpreted as follows: If the user input doesn't change anything, then the guessed variable remains the same, and therefore the user input was wrong.
         * The user input always needs to change something in order to be right!
         */
        if (tmpGuessed == guesses) { // If the tmpGuessed still remains like the old guesses , it means the user has not changed the word
            Beep(200,300);// the program will make a beep sound with 200 Hz and 300 millisecond
            tries--;
            printf("\nWrong guess! You have %d tries left \n", tries);
        }

        for (int i = 0; tmpBuff[i] !='\n'; i++) {
        //  we use \n here because \0 still gives me a "_" after the entire word
            if (tmpBuff[i] == '*') {
                printf("%c",word[i]);// the character was right, print it in the place where it is in the original word.
            } else if( tmpBuff[i] == '\r'){
            // because the words are ending with a '\r' (I can see it when debugging), I want the if statement
            break;
            // to break if it encountered '\r' so it won't show extra characters */
            }
            else{
            // Otherwise, there will be an * to mark the un-guessed letters
                printf("*");
            }
        }
        printf("\n");

        // to check if the user has tires
        while (tries >= 3 && tries <= 8){
            printf("  _______\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("__|_________\n\n");
            break;
        }
        if (tries == 2){
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf("  |\n");
            printf("  |\n");
            printf("  |\n");
            printf("__|_________\n\n");
        }
        if (tries == 1){
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf("  |    |\n");
            printf("  |    |\n");
            printf("  |\n");
            printf("__|_________\n\n");
        }

        if (tries == 0) {
            printf("\n\nEnd of the show:(\n\tThe word is: %s\n\n",word);// The user has lost
            Beep(200,900);
            printf("  _______\n");
            printf("  |/   | \n");
            printf("  |    O \n");
            printf(" ||   \\|/\n");
            printf("  |    | \n");
            printf("  |   / \\\n");
            printf("__|_________\n\n");
            fprintf(log,"The show ended show\n"); // Prints the loss statement to the log file
            printf("returning to main menu..\n");
            sleep(5);
        }
}

    if (guesses == length) {         //to check if the user won
        printf("\n\nYou guessed the word : %s\nCONGRATULATIONS!\n", word);
        // Prints the win message
        fprintf(log, "Player won.\n\n");
        // Prints the win to the log file*/
        printf("returning to main menu...\n");
        sleep(5);
    }

    time(&timeStamp);
    fprintf(log, "The show ended at: %s\n\n",ctime(&timeStamp));
    // write when was the game ended in the log file
    fclose(log);
    // closes the log file

}