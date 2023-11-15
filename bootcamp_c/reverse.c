//ex00
#include <stdio.h>

char* reverse_string(char* param_1) {
    if (param_1 == NULL || *param_1 == '\0') {
        return param_1; // Si la cha�ne est vide ou nulle, retourner telle quelle
    }

    char* end = param_1; // Pointeur vers le d�but de la cha�ne
    char* debut = param_1;

    // Trouver la fin de la cha�ne
    while (*end != '\0') {
        end++;
    }
    end--; // Pointeur sur le dernier caract�re, pas sur le caract�re nul

    // Inversion de la cha�ne
    while (debut < end) {
        // �change des caract�res aux positions param_1 et end
        char temp = *debut;
        *debut = *end;
        *end = temp;

        // D�placer les pointeurs vers le milieu de la cha�ne
        debut++;
        end--;
    }

    return param_1; // Retourne la cha�ne invers�e
}

/*int main() {
    char my_str[] = "Hello";

    printf("Before reverse -> %s\n", my_str);
    printf("Reverse -> %s\n", reverse_string(my_str));
    return 0;
}*/

//ex01

int my_strcmp(char* param_1, char* param_2)
{
    if(param_1 == NULL || param_2 == NULL || strlen(param_1) != strlen(param_2) ){
        return -1;
    }
    while(param_1 != '\0'){
        if(*param_1 != *param_2){
            return -1;
        }
        param_1++;
        param_2++;
    }

     return 0;
}
int main() {
  char *s1 = "Hello";
  char *s2 = "Hello";

  printf("my_strcmp -> %d\n", my_strcmp(s1, s2));
  return 0;
}
