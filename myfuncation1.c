#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * customPrintUnsigned - Prints an unsigned number
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed.
 */
int customPrintUnsigned(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    int i = BUFF_SIZE - 2;
    unsigned long int number = va_arg(argList, unsigned long int);

    number = convertSizeUnsigned(number, outputSize);

    if (number == 0)
        outputBuffer[i--] = '0';

    outputBuffer[BUFF_SIZE - 1] = '\0';

    while (number > 0) {
        outputBuffer[i--] = (number % 10) + '0';
        number /= 10;
    }

    i++;

    return writeUnsigned(0, i, outputBuffer, formatFlags, outputWidth, outputPrecision, outputSize);
}/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * customPrintOctal - Prints an unsigned number in octal notation
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintOctal(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {

    int i = BUFF_SIZE - 2;
    unsigned long int number = va_arg(argList, unsigned long int);
    unsigned long int initialNumber = number;

    UNUSED(outputWidth);

    number = convertSizeUnsigned(number, outputSize);

    if (number == 0)
        outputBuffer[i--] = '0';

    outputBuffer[BUFF_SIZE - 1] = '\0';

    while (number > 0) {
        outputBuffer[i--] = (number % 8) + '0';
        number /= 8;
    }

    if (formatFlags & F_HASH && initialNumber != 0)
        outputBuffer[i--] = '0';

    i++;

    return writeUnsigned(0, i, outputBuffer, formatFlags, outputWidth, outputPrecision, outputSize);
}
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @args: Lista of arguments
 * @output_buffer: Buffer array to handle print
 * @format_flags:  Calculates active flags
 * @output_width: get width
 * @output_precision: Precision specification
 * @output_size: Size specifier
 * Return: Number of chars printed
 */
int custom_print_hexadecimal(va_list args, char output_buffer[],
    int format_flags, int output_width, int output_precision, int output_size)
{
    return (customPrintHexa(args, "0123456789abcdef", output_buffer,
        format_flags, 'x', output_width, output_precision, output_size));
}


/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * customPrintHexaUpper - Prints an unsigned number in upper hexadecimal notation
 * @argList: List of arguments
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintHexaUpper(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize) {
    return customPrintHexa(argList, "0123456789ABCDEF", outputBuffer,
        formatFlags, 'X', outputWidth, outputPrecision, outputSize);
}
/************** PRINT HEXADECIMAL NUMBER IN LOWER OR UPPER **************/
/**
 * customPrintHexa - Prints a hexadecimal number in lower or upper case
 * @argList: List of arguments
 * @mapTo: Array of values to map the number to
 * @outputBuffer: Buffer array to handle print
 * @formatFlags: Calculates active flags
 * @flagChar: Flag character for active flags
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification
 * @outputSize: Size specifier
 * Return: Number of characters printed
 */
int customPrintHexa(va_list argList, char mapTo[], char outputBuffer[],
    int formatFlags, char flagChar, int outputWidth, int outputPrecision, int outputSize) {
    int i = BUFF_SIZE - 2;
    unsigned long int number = va_arg(argList, unsigned long int);
    unsigned long int initialNumber = number;

    UNUSED(outputWidth);

    number = convertSizeUnsigned(number, outputSize);

    if (number == 0)
        outputBuffer[i--] = '0';

    outputBuffer[BUFF_SIZE - 1] = '\0';

    while (number > 0) {
        outputBuffer[i--] = mapTo[number % 16];
        number /= 16;
    }

    if (formatFlags & F_HASH && initialNumber != 0) {
        outputBuffer[i--] = flagChar;
        outputBuffer[i--] = '0';
    }

    i++;

    return writeUnsigned(0, i, outputBuffer, formatFlags, outputWidth, outputPrecision, outputSize);
}

