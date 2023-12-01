/*
**
** QWASAR.IO -- alpha_mirror
**
** @param {char*} param_1
**
** @return {char*}
**
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* alpha_mirror(char* param_1) {
    int length = strlen(param_1);
  // length+1 because we will add '\0\
    char* mirror_str = (char*)malloc((length + 1) * sizeof(char));

    if (mirror_str == NULL) {
        return NULL; 
    }

    for (int i = 0; i < length; i++) {
        if (isalpha(param_1[i])) {
            char original = param_1[i];
            char mirror;
            if (isupper(original)) {
                mirror = 'Z' - (original - 'A'); 
            } else {
                mirror = 'z' - (original - 'a'); 
            }
            mirror_str[i] = mirror;
        } else {
            mirror_str[i] = param_1[i]; 
        }
    }
    mirror_str[length] = '\0'; 

    return mirror_str;
}