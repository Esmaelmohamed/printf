#include "main.h"

/**
 * calculateActiveFlags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @currentIndex: Current index in the format string
 * Return: Flags:
 */
int calculateActiveFlags(const char *format, int *currentIndex) {
    int j, currentIdx;
    int flags = 0;
    const char FLAGS_CHARS[] = {'-', '+', '0', '#', ' ', '\0'};
    const int FLAGS_VALUES[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

    for (currentIdx = *currentIndex + 1; format[currentIdx] != '\0'; currentIdx++) {
        for (j = 0; FLAGS_CHARS[j] != '\0'; j++) {
            if (format[currentIdx] == FLAGS_CHARS[j]) {
                flags |= FLAGS_VALUES[j];
                break;
            }
        }

        if (FLAGS_CHARS[j] == 0) {
            break;
        }
    }

    *currentIndex = currentIdx - 1;

    return flags;
}
