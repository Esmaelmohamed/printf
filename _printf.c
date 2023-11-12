#include "main.h"

void flush_buffer(char buffer[], int *buffIndex);

/**
 * _printf - Printf function
 * @format: Format string
 * Return: Number of printed characters.
 */
int _printf(const char *format, ...)
{
    int i, totalPrinted = 0, printedChars = 0;
    int flags, width, precision, size, buffIndex = 0;
    va_list args;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buffIndex++] = format[i];
            if (buffIndex == BUFF_SIZE)
                flush_buffer(buffer, &buffIndex);
            printedChars++;
        }
        else
        {
            flush_buffer(buffer, &buffIndex);
            flags = calculateActiveFlags(format, &i);
            width = calculatePrintWidth(format, &i, args);
            precision = calculatePrintPrecision(format, &i, args);
            size = calculateArgumentSize(format, &i);
            ++i;
            printedChars = handlePrint(format, &i, args, buffer,
                                        flags, width, precision, size);
            if (printedChars == -1)
                return (-1);
            totalPrinted += printedChars;
        }
    }

    flush_buffer(buffer, &buffIndex);

    va_end(args);

    return (totalPrinted);
}

/**
 * flush_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of characters
 * @buffIndex: Index at which to add the next character, represents the length.
 */
void flush_buffer(char buffer[], int *buffIndex)
{
    if (*buffIndex > 0)
        write(1, &buffer[0], *buffIndex);

    *buffIndex = 0;
}
