#include<stdio.h>
#include<string.h>

/*
**instruction de compilation: dans un terminale, taper:
** gcc -Wall -Wextra -Werror -o my_ngram my_ngram.c
**si aucune erreur n est en vue alors ./ my_ngram text1 test2 testn
*/



int main(int argc , char** argv){

    if(argc < 2){
        return 1;
    }

    int compteur_char[256] = {0};
    char* chaine;

    for(int i = 1 ; i < argc ; i++){
        chaine = argv[i];
        while(*chaine != '\0'){
             compteur_char[(int)*chaine]++;
             chaine++;
        }
    }

     for(int j = 0 ; j < 256 ; j++){
         if(compteur_char[j] != 0){
             printf("%c:%d \n", j , compteur_char[j] );
         }
     }

    return 0;
}
