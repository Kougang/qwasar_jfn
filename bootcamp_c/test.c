#include<stdio.h>

int main(){
    // test des pointeurs

    int x = 20;
    int *p = &x;
  printf(" p1, %d",*p);
    *p = 40;
     printf("p2, %d",*p);   
}

// ex00
void my_initializer(int* param_1) {
    *param_1 = 0;
}
//ex01

void my_swap(int* param_1, int* param_2)
{
 int temporaire = *param_2;
 *param_2 = *param_1;
 *param_1 = temporaire;
}
// ex02

int my_strlen(char* param_1)
{
    int longueur = 0;

    while(*param_1 != '\0'){
        longueur++;
        param_1++;
    }
    return longueur;
}
// ex03

#include <unistd.h>

void my_putstr(char* param_1) {
 

    while (*param_1 != '\0') {
        write(1, param_1, 1); // Écriture du caractère actuel
        param_1++;
}}

//ex04
int my_add(int param_1, int param_2) {
    return param_1 + param_2;
}
 //ex05

 int my_sub(int param_1, int param_2)
{
return param_1 - param_2;
}

//ex06


int my_mult(int param_1, int param_2)
{
return param_1 * param_2;
}

//ex07


void my_string_formatting(char* param_1, char* param_2, int param_3) {
    printf("Hello, my name is %s %s, I'm %d.\n", param_1, param_2, param_3);
}
//ex08
int my_string_index(char* param_1, char param_2)
{
 int index = 0;
 while(*param_1 != '\0'){
    if(*param_1==param_2){
        return index;
    }
    index++;
    param_1++;
 }
 return -1;
}

//ex09

char* my_upcase(char* param_1) {
    int index = 0;
    while (param_1[index] != '\0') {
        if (param_1[index] >= 'a' && param_1[index] <= 'z') {
            param_1[index] = param_1[index] - 32; 
        }
        index++;
    }
    return param_1;
}

// ex10

char* my_downcase(char* param_1) {
    int index = 0;
    while (param_1[index] != '\0') {
        if (param_1[index] >= 'A' && param_1[index] <= 'Z') {
            param_1[index] = param_1[index] + 32; 
        }
        index++;
    }
    return param_1;
}

//quest03
// ex00





