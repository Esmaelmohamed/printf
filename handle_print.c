#include "main.h"

/**
 * handlePrint - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @currentIndex: Current index in the format string.
 * @argumentList: List of arguments to be printed.
 * @outputBuffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @outputWidth: Get width.
 * @outputPrecision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed or -1 on error.
 */
int handlePrint(const char *format, int *currentIndex, va_list argumentList,
                 char outputBuffer[], int flags, int outputWidth,
                 int outputPrecision, int size) {
    int i, unknownLength = 0, printedChars = -1;

    FormatSpecifier formatSpecifiers[] = {
        {'c', customPrintChar}, {'s', customPrintString}, {'%', customPrintPercent},
        {'i', customPrintInt}, {'d', customPrintInt}, {'b', customPrintBinary},
        {'u', customPrintBinary}, {'o', customPrintOctal}, {'x', custom_print_hexadecimal},
        {'X', customPrintHexaUpper}, {'p', customPrintPointer}, {'S', customPrintNonPrintable},
        {'r', customPrintReverse}, {'R', customPrintRot13String}, {'\0', NULL}
    };

    for (i = 0; formatSpecifiers[i].specifier != '\0'; i++) {
        if (format[*currentIndex] == formatSpecifiers[i].specifier) {
            return formatSpecifiers[i].printFunction(argumentList, outputBuffer,
                                                     flags, outputWidth,
                                                     outputPrecision, size);
        }
    }

    if (formatSpecifiers[i].specifier == '\0') {
        if (format[*currentIndex] == '\0') {
            return -1;
        }

        unknownLength += write(1, "%%", 1);

        if (format[*currentIndex - 1] == ' ') {
            unknownLength += write(1, " ", 1);
        } else if (outputWidth) {
            --(*currentIndex);
            while (format[*currentIndex] != ' ' && format[*currentIndex] != '%') {
                --(*currentIndex);
            }
            if (format[*currentIndex] == ' ') {
                --(*currentIndex);
            }
            return 1;
        }

        unknownLength += write(1, &format[*currentIndex], 1);

        return unknownLength;
    }

    return printedChars;
}
