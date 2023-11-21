//code effectuant la tache en indic en dessous de ce code
//ce code est present en deux version, la deuxieme version commente est plus compact

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//===================================
//====definition des constantes======
//===================================
#define CODE_LENGTH 4
#define MAX_nombre_Possibilite 10
#define PIECE_COLORS_LENGTH 9
#define PIECE_COLORS "012345678"
//===========================================
//====definition et ecriture de fonctions====
//===========================================

//fonctions de generation automatique du code secret
void generate_secret_code(char *secret_code) {
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
int validate_input(char *input) {
    //test de validite de la longueur et de chaque caractere
    int taille = 0;
    while (input[taille] != '\0') {
        taille++;
    }

    bool taille_valid = (taille == CODE_LENGTH); 
    bool tous_caract_valid = true;

    for (int i = 0; i < CODE_LENGTH; i++) {
        bool caract_valid = false;
        for (int j = 0; PIECE_COLORS[j] != '\0'; j++) {
            if (input[i] == PIECE_COLORS[j]) {
                caract_valid = true;
                break;
            }
        }
        if (!caract_valid) {
            tous_caract_valid = false;  
            break;
        }
    }

    return taille_valid && tous_caract_valide;
}
//===================================
//====fonction d evaluation source===
//===================================
void evaluate_guess(char *guess, char *secret_code, int *bonnePlace, int *mauvaisePlace) {
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
}

//===================================
//====fonction d'affichage===========
//===================================
void display_round_result(int round, int bonnePlace, int mauvaisePlace) {
    printf("---\nRound %d\n>Well placed pieces: %d\n>Misplaced pieces: %d\n", round, bonnePlace, mauvaisePlace);
}

//===================================
//====entree et test dans le main====
//===================================
int main(int argc, char *argv[]) {

    char secret_code[CODE_LENGTH + 1];
    char guess[CODE_LENGTH + 1];
    int bonnePlace, mauvaisePlace;

    if (argc > 1 && strcmp(argv[1], "-c") == 0) {
        if (validate_input(argv[2])) {
            //je recopie le contenu de argv[2] dans le pointeur ou tableau a une dimension secret_code
            for (int i = 0; i < CODE_LENGTH; i++) {
                secret_code[i] = argv[2][i];
            }
        } else {
            printf("Invalid secret code. Exiting.\n");
            return 1;
        }
    } else {
        generate_secret_code(secret_code);
    }

    int nombre_Possibilite = (argc > 3 && strcmp(argv[3], "-t") == 0) ? atoi(argv[4]) : MAX_nombre_Possibilite;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (int round = 0; round < nombre_Possibilite; round++) {
        printf("---\nRound %d\n>", round);
        if (read(0, guess, CODE_LENGTH) < 0) {
            //si l'user press ctrl + d qui correspond a une erreur de lecture
            // fin de fichier (Ctrl + D)
            break;
        }

        guess[CODE_LENGTH] = '\0';

        if (!validate_input(guess)) {
            printf("Wrong input!\n");
            continue;
        }

        evaluate_guess(guess, secret_code, &bonnePlace, &mauvaisePlace);
        display_round_result(round, bonnePlace, mauvaisePlace);

        if (bonnePlace == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            return 0;
        }
    }

    printf("Out of attempts. The secret code was %s\n", secret_code);
    return 0;
}

/**
 ==============================
 ===deuxieme version du code===
 ==============================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//===================================
//====definition des constantes======
//===================================
#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10
#define PIECE_COLORS "012345678"
//===========================================
//====definition et ecriture de fonctions====
//===========================================

//fonctions de generation automatique du code secret
void generate_secret_code(char *secret_code) {
    int i;
    srand(time(NULL));
    for (i = 0; i < CODE_LENGTH; i++) {
        secret_code[i] = PIECE_COLORS[rand() % strlen(PIECE_COLORS)];
    }
    secret_code[CODE_LENGTH] = '\0';
}
//==================================================================
//====fonction de validation de l'enntree standard de l'utilisateur=
//==================================================================
int validate_input(char *input) {
    return strlen(input) == CODE_LENGTH && strspn(input, PIECE_COLORS) == CODE_LENGTH;
}
//===================================
//====fonction d evaluation source===
//===================================
void evaluate_guess(char *guess, char *secret_code, int *well_placed, int *misplaced) {
    *well_placed = 0;
    *misplaced = 0;

    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] == secret_code[i]) {
            (*well_placed)++;
        } else if (strchr(secret_code, guess[i]) != NULL) {
            (*misplaced)++;
        }
    }
}
//===================================
//====fonction d'affichage===========
//===================================
void display_round_result(int round, int well_placed, int misplaced) {
    printf("---\nRound %d\n>Well placed pieces: %d\n>Misplaced pieces: %d\n", round, well_placed, misplaced);
}

//===================================
//====entree et test dans le main====
//===================================
int main(int argc, char *argv[]) {
    char secret_code[CODE_LENGTH + 1];
    char guess[CODE_LENGTH + 1];
    int well_placed, misplaced;

    if (argc > 1 && strcmp(argv[1], "-c") == 0) {
        if (validate_input(argv[2])) {
            strcpy(secret_code, argv[2]);
        } else {
            printf("Invalid secret code. Exiting.\n");
            return 1;
        }
    } else {
        generate_secret_code(secret_code);
    }

    int attempts = (argc > 3 && strcmp(argv[3], "-t") == 0) ? atoi(argv[4]) : MAX_ATTEMPTS;

    printf("Will you find the secret code?\nPlease enter a valid guess\n");

    for (int round = 0; round < attempts; round++) {
        printf("---\nRound %d\n>", round);
        if (read(0, guess, CODE_LENGTH) < 0) {
            //si l'user press ctrl + d qui correspond a une erreur de lecture
            // fin de fichier (Ctrl + D)
            break; 
        }

        guess[CODE_LENGTH] = '\0';

        if (!validate_input(guess)) {
            printf("Wrong input!\n");
            continue;
        }

        evaluate_guess(guess, secret_code, &well_placed, &misplaced);
        display_round_result(round, well_placed, misplaced);

        if (well_placed == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            return 0;
        }
    }

    printf("Out of attempts. The secret code was %s\n", secret_code);
    return 0;
}


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

