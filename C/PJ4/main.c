/**
 * Jecsan Blanco
 * 2018FA OP SYSTEMS & NETWRK (CS-3352-01)
 * Project 4 - Partial manual input output.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int countDigit(int n);

int charToInt(char c);

int strToInt(char *str);

void printLn(char *str);

void printLn(char *str) {
    assert(str != NULL);
    write(1, str, strlen(str)* sizeof(char));
    write(1, "\n", sizeof(char));
}


int countDigit(int n) {
    if (n < 0) n = abs(n);
    return (int) (floor(log10(n))) + 1;
}

/**
 *  Converts any digit [0-9] into its ascii representation.
 */
char inttochar(int n) {
    assert(n >= 0 && n < 10);
    return (char) (n + 0x30);
}


/**
 * A integer into its null terminated string representation.
 */
char *inttostr(int num) {
    int sign = num < 0;
    int digits = countDigit(num) + 1 + sign;
    char *string = malloc((digits) * sizeof(char));
    // handle negatives
    if (sign) {
        string[0] = '-';
        num = abs(num);
    }
    int v = 0;
    for (int i = digits - 2; i >= 0 + sign; --i) {
        v = num % 10;
        string[i] = inttochar(v);
        num /= 10;
    }
    string[digits - 1] = 0;
    return string;
}

/**
 * Turns a single ascii digit into its integer value.
 */
int charToInt(char c) {
    assert(c >= '0' && c <= '9');
    return c & 0x0F;
}

/**
 * Turns a null terminated string of ascii digits to its integer representation.
 */
int strToInt(char *str) {
    assert(str != NULL);
    int sign = (str[0] == '-') ? 1 : 0;
    if (sign) ++str;
    int digits = (int) strlen(str);

    int result = 0;
    int magnitude = 1;
    for (int i = digits - 1; i >= 0; --i) {
        result += charToInt(str[i]) * magnitude;
        magnitude *= 10;
    }
    return (sign) ? result * -1 : result;
}

/**
 * Asks for two integers separated by a space to be added.
 */
int main(int argc, char *argv[]) {
    char *input, *a, *b, *output;
    char delimiter;
    int result;
    int buffer_size;

    delimiter = ' ';
    buffer_size = 255;

    input = (char *) malloc(buffer_size * sizeof(char));
    printLn("Enter two numbers on one line separated by a space.");
    read(1, input, (size_t) 256);
    assert(input != NULL);

    //first number and second numbers
    b = input;
    a = strsep(&input, &delimiter);
    //removes the newline
    b[strcspn(b, "\n")] = 0;

    //do the thing
    result = strToInt(a) + strToInt(b);
    output = inttostr(result);
    printLn("Sum of the two numbers you entered = ");
    printLn(output);
    //Land of the
    free(a);
    free(output);
    return 0;
}