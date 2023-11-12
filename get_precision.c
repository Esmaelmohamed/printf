#include "main.h"

/**
 * calculatePrintPrecision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @currentIndex: Current index in the format string
 * @argumentList: List of arguments to be printed
 *
 * Return: Precision
 */
int calculatePrintPrecision(const char *format, int *currentIndex, va_list argumentList) {
    int currentIdx = *currentIndex + 1;
    int precision = -1;

    if (format[currentIdx] != '.')
        return precision;

    precision = 0;

    for (currentIdx += 1; format[currentIdx] != '\0'; currentIdx++) {
        if (isDigit(format[currentIdx])) {
            precision *= 10;
            precision += format[currentIdx] - '0';
        } else if (format[currentIdx] == '*') {
            currentIdx++;
            precision = va_arg(argumentList, int);
            break;
        } else {
            break;
        }
    }

    *currentIndex = currentIdx - 1;

    return precision;
}
