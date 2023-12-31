#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include  <stdio.h>


char* reverse_call(char* str, int length){
       // Reverse the string
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }

    str[length] = '\0'; // Null-terminate string

    return str;
}

char *itoa_dec(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Handle negative numbers
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    // Process individual digits in reverse order
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    // Append negative sign for negative numbers
    if (is_negative) {
        str[i++] = '-';
    }

    
    return reverse_call(str,i);
}

char *itoa_oct(int num, char *str) {
    // Implementation de la conversion en base octale
    int i = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Process individual digits in reverse order
    while (num != 0) {
        int rem = num % 8;
        str[i++] = rem + '0';
        num = num / 8;
    }

   return reverse_call(str,i);
}

char *itoa_hex(int num, char *str) {
    // Implementation de la conversion en base hexadécimale
    int i = 0;
    const char *hex_chars = "0123456789ABCDEF";  // Hex chars in uppercase

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Process individual digits in reverse order
    while (num != 0) {
        int rem = num % 16;
        str[i++] = hex_chars[rem];
        num = num / 16;
    }

   return reverse_call(str,i);
}

char *intptr_to_hex(long num, char *str) {
    // Implementation de la conversion en base hexadécimale
    long i = 0;
    const char *hex_chars = "0123456789abcdef";  // Hex chars in uppercase

    while (num != 0) {
        long rem = num % 16;
        str[i++] = hex_chars[rem];
        num = num / 16;
    }
    str[i] = 'x';
    i ++;
    str[i] = '0';
    i ++;
    // Reverse the string
    long start = 0;
    long end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    str[i] = '\0'; // Null-terminate string
    return str;
}

char *utoa_dec(unsigned int num, char *str) {
    int i = 0;

    // Handle 0 explicitly, otherwise empty string is printed
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Process individual digits in reverse order
    while (num != 0) {
        int rem = num % 10;
        str[i++] = rem + '0';
        num = num / 10;
    }

    return reverse_call(str,i);
}

// Custom implementation of printf
int my_printf(char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    int written = 0;
    char *str;
    int num;
    unsigned int u_num;  // Use unsigned int for %u
    intptr_t ptr_value;


    while (*format) {
        if (*format == '%') {
            format++;

            switch (*format) {
                case 'd':
                    num = va_arg(args, int);
                    char num_str[12]; // Assuming a 32-bit int
                    itoa_dec(num, num_str);
                    written += write(1, num_str, strlen(num_str));
                    break;

                case 'o':
                    num = va_arg(args, unsigned int);
                    char octalStr[12]; // Assuming a 32-bit int
                    itoa_oct(num, octalStr);
                    written += write(1, octalStr, strlen(octalStr));
                    break;

                case 'x':
                    num = va_arg(args, unsigned int);
                    char hex_str[12]; // Assuming a 32-bit int
                    itoa_hex(num, hex_str);
                    written += write(1, hex_str, strlen(hex_str));
                    break;

                case 'c':
                    num = va_arg(args, int);
                    written += write(1, &num, 1);
                    break;

                case 's':
                    str = va_arg(args, char *);

                    if (str != NULL) {
                        written += write(1, str, strlen(str));
                    } else {
                        written += write(1, "(null)", 6);
                    }
                    break;

                case 'p':

                    ptr_value = (intptr_t)va_arg(args, void *);
                    char hex_strs[16]; // Assuming a 64-bit pointer
                    intptr_to_hex(ptr_value, hex_strs);

                    written += write(1, hex_strs, strlen(hex_strs));
                   
                    break;
                    
                case 'u':
                    u_num = va_arg(args, unsigned int);
                    char u_num_str[12]; // Assuming a 32-bit unsigned int
                    utoa_dec(u_num, u_num_str);
                    written += write(1, u_num_str, strlen(u_num_str));
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
    int var = 24;
    my_printf("Hexadecimal: %x, Octal: %o,  Decimal: %d, pointeur: %p\n", 10, 10, 10, &var);

    return 0;
}// // printf("printf() %%p: %p\n", &var);
    // my_printf("my_printf() %%p: %p\n", &var);
    // printf("printf() %%x: %X\n", 1234);
    // my_printf("my_printf() %%x: %x\n", 1234);





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
