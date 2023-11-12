#include "main.h"

/**
 * calculatePrintWidth - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @currentIndex: Current index in the format string.
 * @argumentList: List of arguments to be printed.
 *
 * Return: Width.
 */
int calculatePrintWidth(const char *format, int *currentIndex, va_list argumentList) {
    int currentIdx;
    int width = 0;

    for (currentIdx = *currentIndex + 1; format[currentIdx] != '\0'; currentIdx++) {
        if (isDigit(format[currentIdx])) {
            width *= 10;
            width += format[currentIdx] - '0';
        } else if (format[currentIdx] == '*') {
            currentIdx++;
            width = va_arg(argumentList, int);
            break;
        } else {
            break;
        }
    }

    *currentIndex = currentIdx - 1;

    return width;
}
