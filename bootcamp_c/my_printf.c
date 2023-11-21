#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// Function to convert an integer to a string
char *itoa(int num, char *str, int base) {
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Handle negative numbers for bases other than 10
    if (num < 0 && base != 10) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    // Append negative sign for negative numbers
    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0'; // Null-terminate string
    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    return str;
}

// Custom implementation of printf
int my_printf(char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0;
    char *str;
    int num;

    while (*format) {
        if (*format == '%') {
            format++;

            switch (*format) {
                case 'd':
                    num = va_arg(args, int);
                    char numStr[12]; // Assuming a 32-bit int
                    itoa(num, numStr, 10);
                    written += write(1, numStr, strlen(numStr));
                    break;

                case 'o':
                    num = va_arg(args, unsigned int);
                    char octalStr[12]; // Assuming a 32-bit int
                    itoa(num, octalStr, 8);
                    written += write(1, octalStr, strlen(octalStr));
                    break;

                case 'u':
                    num = va_arg(args, unsigned int);
                    char unsignedStr[12]; // Assuming a 32-bit int
                    itoa(num, unsignedStr, 10);
                    written += write(1, unsignedStr, strlen(unsignedStr));
                    break;

                case 'x':
                    num = va_arg(args, unsigned int);
                    char hexStr[12]; // Assuming a 32-bit int
                    itoa(num, hexStr, 16);
                    written += write(1, hexStr, strlen(hexStr));
                    break;

                case 'c':
                    num = va_arg(args, int);
                    written += write(1, &num, 1);
                    break;

                case 's':
                    str = va_arg(args, char *);
                    written += write(1, str, strlen(str));
                    break;

                case 'p':
                    num = (int)(intptr_t)va_arg(args, void *);
                    char ptrStr[12]; // Assuming a 32-bit pointer
                    itoa(num, ptrStr, 16);
                    written += write(1, ptrStr, strlen(ptrStr));
                    break;

                default:
                    written += write(1, format, 1);
                    break;
            }
        } else {
            written += write(1, format, 1);
        }

        format++;
    }

    va_end(args);
    return written;
}

int main() {
    my_printf("Hello, %s! My favorite number is %d. Pointer: %p\n", "World", 42, (void *)main);
    return 0;
}










/**
Description
NAME
int my_printf(char * restrict format, ...);

Prolog
The very first thing we do when learning a programming language is to write "Hello World !" on the screen. Well guess what ? This custom comes from a notebook called ... Programming in C: A Tutorial !

Unfortunately for you, this project will bring you back in the 1970s, before the existence of this book, and you will have to write your own function to greet the world.

Fortunately for you, you will strengthen your programming skills and learn new programming concepts: variadic functions and variable argument lists. Recoding printf is also a good exercise to learn to have
a well structured code organisation. Modularity is the key here since printf has a lot of different options that you will have to recode yourself. Adding a new option feature should be easy and smooth if
the code is well designed !

DESCRIPTION
The my_printf() function produce output according to a format as described below. The my_printf() functions write output to stdout, the standard output stream;

This function writes the output under the control of a format string that specifies how subsequent arguments (or arguments accessed via the variable-length argument facilities of stdarg(3)) are converted for output.

The format string is composed of zero or more directives: ordinary characters (not PERCENT), which are copied unchanged to the output stream; and conversion specifications, each of which results in fetching zero or more subsequent arguments.

Each conversion specification is introduced by the PERCENT character. The arguments must correspond properly (after type promotion) with the conversion specifier. After the PERCENT, the following appear in sequence:

doux The int (or appropriate variant) argument is converted to signed decimal (d). unsigned octal (o), unsigned decimal (u), unsigned hexadecimal (x).
c The int argument is converted to an unsigned char, and the resulting character is written.
s The char * argument is expected to be a pointer to an array of character type (pointer to a string). Characters from the array are written up to (but not including) a terminating NUL character.
p The void * pointer argument is printed in hexadecimal.
Requirements
Your code must be compiled with the flags -Wall -Wextra -Werror.
Hint(s)
• man printf

• man 3 stdarg

• Watch out for memory leaks !

• You can test your code against memory errors by compiling with the debugging flags -g3 -fsanitize=address

• Global variables are strictly FORBIDDEN

• Static variables are strictly FORBIDDEN

Authorized function(s)
• write(2)
• malloc
• free
• va_start, va_arg, va_copy, va_end (see man 3 stdarg)
(Obvious) Unauthorized functions
printf and co. (fprintf, sprintf, snprintf, asprintf, dprintf, vprintf, vfprintf, vsprintf, vsnprintf, vasprintf, vdprintf)
Multiline macros are forbidden
Include another .c is forbidden
Macros with logic (while/if/variables/...) are forbidden
Epilog
Don't forget you can ask questions on the chat !

Good luck!
**/