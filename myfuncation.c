#include "main.h"
/**
 * customPrintChar - Prints a character
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Width
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */

int customPrintChar(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    char character = va_arg(argList, int);

    return (writeChar(character, outputBuffer, formatFlags, outputWidth, outputPrecision, outputSize));
}

/************************* PRINT A STRING *************************/
/**
 * customPrintString - Prints a string
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintString(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    int length = 0, i;
    char *str = va_arg(argList, char *);

    UNUSED(outputBuffer);
    UNUSED(formatFlags);
    UNUSED(outputWidth);
    UNUSED(outputPrecision);
    UNUSED(outputSize);
    if (str == NULL) {
        str = "(null)";
        if (outputPrecision >= 6)
            str = "      ";
    }

    while (str[length] != '\0')
        length++;

    if (outputPrecision >= 0 && outputPrecision < length)
        length = outputPrecision;

    if (outputWidth > length) {
        if (formatFlags & F_MINUS) {
            write(1, &str[0], length);
            for (i = outputWidth - length; i > 0; i--)
                write(1, " ", 1);
            return (outputWidth);
        } else {
            for (i = outputWidth - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (outputWidth);
        }
    }

    return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * customPrintPercent - Prints a percent sign
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintPercent(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    UNUSED(argList);
    UNUSED(outputBuffer);
    UNUSED(formatFlags);
    UNUSED(outputWidth);
    UNUSED(outputPrecision);
    UNUSED(outputSize);
    return (write(1, "%%", 1));
}
/************************* PRINT INTEGER *************************/
/**
 * customPrintInt - Print integer
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintInt(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    int i = BUFF_SIZE - 2;
    int isNegative = 0;
    long int number = va_arg(argList, long int);
    unsigned long int num;

    number = convertSizeNumber(number, outputSize);

    if (number == 0)
        outputBuffer[i--] = '0';

    outputBuffer[BUFF_SIZE - 1] = '\0';
    num = (unsigned long int)number;

    if (number < 0) {
        num = (unsigned long int)((-1) * number);
        isNegative = 1;
    }

    while (num > 0) {
        outputBuffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (writeNumber(isNegative, i, outputBuffer, formatFlags, outputWidth, outputPrecision, outputSize));
}
/************************* PRINT BINARY *************************/
/**
 * customPrintBinary - Prints an unsigned number in binary
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintBinary(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    unsigned int num, divisor, i, sum;
    unsigned int binaryArray[32];
    int count;

    UNUSED(outputBuffer);
    UNUSED(formatFlags);
    UNUSED(outputWidth);
    UNUSED(outputPrecision);
    UNUSED(outputSize);

    num = va_arg(argList, unsigned int);
    divisor = 2147483648; /* (2 ^ 31) */
    binaryArray[0] = num / divisor;

    for (i = 1; i < 32; i++) {
        divisor /= 2;
        binaryArray[i] = (num / divisor) % 2;
    }

    for (i = 0, sum = 0, count = 0; i < 32; i++) {
        sum += binaryArray[i];
        if (sum || i == 31) {
            char binaryChar = '0' + binaryArray[i];
            write(1, &binaryChar, 1);
            count++;
        }
    }

    return count;
}


