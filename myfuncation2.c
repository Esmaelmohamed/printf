#include "main.h"
/****************** PRINT POINTER ******************/
/**
 * customPrintPointer - Prints the value of a pointer variable
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed.
 */
int customPrintPointer(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    char extraChar = 0, paddingChar = ' ';
    int index = BUFF_SIZE - 2, length = 2, paddingStart = 1; /* length=2, for '0x' */
    unsigned long numAddresses;
    char mapTo[] = "0123456789abcdef";
    void *addresses = va_arg(argList, void *);

    UNUSED(outputWidth);
    UNUSED(outputSize);

    if (addresses == NULL)
        return write(1, "(nil)", 5);

    outputBuffer[BUFF_SIZE - 1] = '\0';
    UNUSED(outputPrecision);

    numAddresses = (unsigned long)addresses;

    while (numAddresses > 0) {
        outputBuffer[index--] = mapTo[numAddresses % 16];
        numAddresses /= 16;
        length++;
    }

    if ((formatFlags & F_ZERO) && !(formatFlags & F_MINUS))
        paddingChar = '0';

    if (formatFlags & F_PLUS)
        extraChar = '+', length++;
    else if (formatFlags & F_SPACE)
        extraChar = ' ', length++;

    index++;

    return writePointer(outputBuffer, index, length,
        outputWidth, formatFlags, paddingChar, extraChar, paddingStart);
}

/************************* PRINT NON-PRINTABLE *************************/
/**
 * customPrintNonPrintable - Prints ASCII codes in hexadecimal of non-printable characters
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintNonPrintable(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    int i = 0, offset = 0;
    char *str = va_arg(argList, char *);

    UNUSED(formatFlags);
    UNUSED(outputWidth);
    UNUSED(outputPrecision);
    UNUSED(outputSize);

    if (str == NULL)
        return write(1, "(null)", 6);

    while (str[i] != '\0') {
        if (isPrintable(str[i]))
            outputBuffer[i + offset] = str[i];
        else
            offset += appendHexaCode(str[i], outputBuffer, i + offset);

        i++;
    }

    outputBuffer[i + offset] = '\0';

    return write(1, outputBuffer, i + offset);
}

/************************* PRINT REVERSE *************************/
/**
 * customPrintReverse - Prints a reversed string.
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintReverse(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    char *str;
    int i, count = 0;

    UNUSED(outputBuffer);
    UNUSED(formatFlags);
    UNUSED(outputWidth);
    UNUSED(outputSize);

    str = va_arg(argList, char *);

    if (str == NULL) {
        UNUSED(outputPrecision);
        str = "(Null)";
    }

    for (i = 0; str[i]; i++)
        ;

    for (i = i - 1; i >= 0; i--) {
        char reversedChar = str[i];
        write(1, &reversedChar, 1);
        count++;
    }

    return count;
}

/************************* PRINT STRING IN ROT13 *************************/
/**
 * customPrintRot13String - Prints a string in ROT13.
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintRot13String(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    char x;
    char *str;
    unsigned int i, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(argList, char *);

    UNUSED(outputBuffer);
    UNUSED(formatFlags);
    UNUSED(outputWidth);
    UNUSED(outputPrecision);
    UNUSED(outputSize);

    if (str == NULL)
        str = "(AHYY)";

    for (i = 0; str[i]; i++) {
        for (j = 0; in[j]; j++) {
            if (in[j] == str[i]) {
                x = out[j];
                write(1, &x, 1);
                count++;
                break;
            }
        }
        if (!in[j]) {
            x = str[i];
            write(1, &x, 1);
            count++;
        }
    }

    return count;
}

