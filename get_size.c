#include "main.h"

/**
 * calculateArgumentSize - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @currentIndex: Current index in the format string
 *
 * Return: Size specification
 */
int calculateArgumentSize(const char *format, int *currentIndex) {
    int currentIdx = *currentIndex + 1;
    int size = 0;

    if (format[currentIdx] == 'l') {
        size = S_LONG;
    } else if (format[currentIdx] == 'h') {
        size = S_SHORT;
    }

    if (size == 0) {
        *currentIndex = currentIdx - 1;
    } else {
        *currentIndex = currentIdx;
    }

    return size;
}
