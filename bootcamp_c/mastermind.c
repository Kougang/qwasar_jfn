// ================================
//fivhier d entete my mastermind.h:
//=================================
/**
#ifndef MY_MASTERMIND_H
#define MY_MASTERMIND_H

#define CODE_LENGTH 4
#define MAX_NUMBER_POSSIBILITY 10
#define PIECE_COLORS_LENGTH 9
#define PIECE_COLORS "012345678"
#define MAX_INPUT_LENGTH 100


void generate_secret_code(char *secret_code);
int validate_input(char *input);
void evaluate_guess(char *guess, char *secret_code, int *bonnePlace, int *mauvaisePlace);
void display_round_result(int bonnePlace, int mauvaisePlace);
#endif 
**/

#include "my_mastermind.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//===================================
//====fichier all_function.c   ======
//===================================
//fonctions de generation automatique du code secret
void generate_secret_code(char* secret_code) {
    int i;
    srand(time(NULL));
    for (i = 0; i < CODE_LENGTH; i++) {
        secret_code[i] = PIECE_COLORS[rand() % PIECE_COLORS_LENGTH];
    }
    secret_code[CODE_LENGTH] = '\0';
}

//==================================================================
//====fonction de validation de l'enntree standard de l'utilisateur=
//==================================================================
int validate_input(char* input) {
  int valid = 1;
  int input_length = 0;

  while (input[input_length] != '\0') {
    input_length++;
  }

  if (input_length != CODE_LENGTH) {
    valid = 0;
  } else {
    int valid_input = 1;
    for (int i = 0; i < CODE_LENGTH; i++) {
      valid_input = 0;
      for (int j = 0; j < PIECE_COLORS_LENGTH; j++) {
        if (input[i] == PIECE_COLORS[j]) {
          valid_input = 1;
          break;
        }
      }
      if (!valid_input) {
        valid = 0;
        break;
      }
    }
  }
  
  return valid;
}
//===================================
//====fonction d evaluation source===
//===================================
void evaluate_guess(char* guess, char* secret_code, int* bonnePlace, int* mauvaisePlace) {
    *bonnePlace = 0;
    *mauvaisePlace = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] == secret_code[i]) {
            (*bonnePlace)++;
        } else {
            for (int j = 0; j < CODE_LENGTH; j++) {
                if (i != j && guess[i] == secret_code[j]) {
                    (*mauvaisePlace)++;
                    break;  
                }
            }
        }
    }
    //   printf("Current guess: %s, Well placed pieces: %d, Misplaced pieces: %d\n", guess, *bonnePlace, *mauvaisePlace);

}

//===================================
//====fonction d'affichage===========
//===================================
void display_round_result(int bonnePlace, int mauvaisePlace) {

    printf("Well placed pieces: %d\nMisplaced pieces: %d\n",bonnePlace, mauvaisePlace);

}


//===================================
//====entree et test dans le main====
//===================================
int main(int argc, char* argv[]) {

    int new_long = CODE_LENGTH + 1;
    char secret_code[new_long];
    char guess[new_long];
    // char inter[new_long];
    int bonnePlace, mauvaisePlace;
    char c;
    // char input[100];
    // int bytes_read;

    if (argc > 1 && strcmp(argv[1], "-c") == 0) {
        if (validate_input(argv[2])) {
            //je recopie le contenu de argv[2] dans le pointeur ou tableau a une dimension secret_code
            for (int i = 0; i < CODE_LENGTH; i++) {
                secret_code[i] = argv[2][i];
            }
        } else {
            printf("Invalid secret code Exiting\n");
            return 1;
        }
    } else {
        generate_secret_code(secret_code);
    }

    int nombre_Possibilite = (argc > 3 && strcmp(argv[3], "-t") == 0) ? atoi(argv[4]) : MAX_NUMBER_POSSIBILITY;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    // inter[0] = guess[0];
    for (int round = 0; round < nombre_Possibilite; round++) {
    //     printf("Round %d\n", round);
    //    *guess = '\0';
        int i = 0;
        while( (read(0, &c, 1) == 1)){
            if ( c == '\n') {
                guess[i] = '\0';
                break;
            }
            guess[i] = c;
            i++;
        }
        // guess[CODE_LENGTH] = '\0';

        if (!validate_input(guess)) {
            // printf("Will you find the secret code!\n");
            continue;
        }

        evaluate_guess(guess, secret_code, &bonnePlace, &mauvaisePlace);
        
        if (bonnePlace == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            // write(STDOUT_FILENO, "Congratz! You did it!\n", 23);
            return 0;
        }
        display_round_result(bonnePlace, mauvaisePlace);
    }

    printf("Out of attempts. The secret code was %s\n", secret_code);
    return 0;
}












/**
 ==============================
 ===deuxieme version du code===
 ==============================

**/

//enonce de l exercice ci dessous
/**
My Mastermind
Submit directory	.
Submit files	Makefile - *.c - *.h
Description
SPECIFICATIONS
Write a program called mastermind; it will be an implementation of the famous game.

NAME
my_mastermind

SYNOPSIS
my_mastermind [-ct]

DESCRIPTION
Mastermind is a game composed of 9 pieces of different colors.
A secret code is then composed of 4 distinct pieces.

The player has 10 attempts to find the secret code.
After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.

If the player finds the code, he wins, and the game stops.
A misplaced piece is a piece that is present in the secret code butthat is not in a good position.

You must read the player's input from the standard input.

Your program will also receive the following parameters:
-c [CODE]: specifies the secret code. If no code is specified, a random code will be generated.
-t [ATTEMPTS]: specifies the number of attempts; by default, the playerhas 10 attempts.

Example 00

PROMPT>./my_mastermind -c "0123"
Will you find the secret code?
Please enter a valid guess
---
Round 0
>1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Congratz! You did it!
Technical information
you must create a Makefile, and the ouput is the command itself
It will contain rule all/clean/fclean (re => fclean + all)

You can use:

printf(3)
write(2)
read(2)
rand() (/ srand())
time()
atoi()
strcmp()
You can NOT use:
Any functions/syscalls which does not appear in the previous list
Yes, it includes exit
Consider writing a README.md to describe your project and how it works.

Your mastermind needs to handle the sequence Ctrl + d. It's End Of File.
It's consider as a normal execution.

read() is a syscall difficult to apprehend, you will have time to deal more with it in a later project. In this project, you should read 1 character by 1 (use read(0, &c, 1)) and add them one by one to a buffer until you encounter a newline.

Example:

[/tmp/]bash
bash-3.2$ exit
[/tmp/]
In this example, bash exited successfully and also printed "exit".

Output formats
When your program starts, you must display:
Will you find the secret code?
Please enter a valid guess
When the user wins, you must display:
Congratz! You did it!
When the user enters an invalid code, you must respect the following format:
Well placed pieces: X
Misplaced pieces: Y
X and Y are two digits with the correct values.

Requirements
Your code must be compiled with the flags -Wall -Wextra -Werror.
Multiline macros are forbidden
You should have multiple file .c but it's forbidden to include them (#include another_file.c) use your Makefile to compile them together.
Macros with logic (while/if/variables/...) are forbidden
Advanced Testing
Gandalf tests using a synthax similar to this one:

echo "1234
2345
3456" | ./my_mastermind -c 3456
It will hightlight that you are not using read() well.

Hint(s)
man 2 read
man rand
Makefile, case sensitivity is important.
**/
// ==============================================
// ==============================================
// ==============================================
// ==============================================
// ==============================================
// ==============================================
// ==============================================

//code effectuant la tache en indic en dessous de ce code
