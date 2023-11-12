#include "main.h"

/**
 * isPrintable - Evaluates if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: 1 if c is printable, 0 otherwise
 */
int isPrintable(char c) {
    if (c >= 32 && c < 127)
        return 1;

    return 0;
}

/**
 * appendHexaCode - Append ASCII in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @index: Index at which to start appending.
 * @asciiCode: ASCII CODE.
 * Return: Always 3
 */
int appendHexaCode(char asciiCode, char buffer[], int index) {
    char hexMap[] = "0123456789ABCDEF";
    /* The hexadecimal format code is always 2 digits long */
    if (asciiCode < 0)
        asciiCode *= -1;

    buffer[index++] = '\\';
    buffer[index++] = 'x';

    buffer[index++] = hexMap[asciiCode / 16];
    buffer[index] = hexMap[asciiCode % 16];

    return 3;
}

/**
 * isDigit - Verifies if a char is a digit
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int isDigit(char c) {
    if (c >= '0' && c <= '9')
        return 1;

    return 0;
}

/**
 * convertSizeNumber - Casts a number to the specified size
 * @num: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of num
 */
long int convertSizeNumber(long int num, int size) {
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (short)num;

    return (int)num;
}

/**
 * convertSizeUnsigned - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convertSizeUnsigned(unsigned long int num, int size) {
    if (size == S_LONG)
        return num;
    else if (size == S_SHORT)
        return (unsigned short)num;

    return (unsigned int)num;
}
