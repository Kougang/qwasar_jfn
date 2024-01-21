/*
**
** QWASAR.IO -- last_word
**
** @param {char*} param_1
**
** @return {char*}
**
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



char* last_word(char* param_1)
{
    int length = strlen(param_1);

    // deleted the last space after last word
    int i = length - 1;
    while (i >= 0 && (param_1[i] == ' ' || param_1[i] == '\t')) {
        i--;
    }

    int j = 0;
    // find the last word
    while (i >= 0 && ((param_1[i-1] != ' ' ) && (param_1[i-1] != ',' )) && param_1[i-1] != '\t') {
        i--;
        j++;
    }

    if (i >= 0) {
        int word_length = j + 1;
        char* last_word = malloc((word_length) * sizeof(char));
        strncpy(last_word, &param_1[i], word_length);
        last_word[word_length] = '\0';
        return last_word;
    } else {
        char* empty_str= malloc(1);
        empty_str[0] = '\0';
        return empty_str;
    }
}
