#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1
struct specifier
{
	char specifier;
	int (*printFunction)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct specifier FormatSpecifier - Struct op
 *
 * @specifier: The format.
 * @FormatSpecifier: The function associated.
 */
typedef struct specifier FormatSpecifier;
int _printf(const char *format, ...);
int handlePrint(const char *format, int *currentIndex, va_list argumentList,
                 char outputBuffer[], int flags, int outputWidth,
                 int outputPrecision, int size);
/* Function to print chars and strings */
 int customPrintChar(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
int customPrintString(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
    int customPrintPercent(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
    int customPrintInt(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
    int customPrintBinary(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);

/* Functions to print numbers */
int customPrintUnsigned(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
   int customPrintOctal(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
    int custom_print_hexadecimal(va_list args, char output_buffer[],
    int format_flags, int output_width, int output_precision, int output_size);
    int customPrintHexaUpper(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
    int customPrintHexa(va_list argList, char mapTo[], char outputBuffer[],
    int formatFlags, char flagChar, int outputWidth, int outputPrecision, int outputSize);

/* Function to print non printable characters */
int customPrintNonPrintable(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
int customPrintPointer(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
    
/* Functions to handle other specifiers */
int calculateActiveFlags(const char *format, int *currentIndex);
int calculatePrintWidth(const char *format, int *currentIndex, va_list argumentList);
int calculatePrintPrecision(const char *format, int *currentIndex, va_list argumentList);
int calculateArgumentSize(const char *format, int *currentIndex);
/* Function to print string in reverse */
int customPrintReverse(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);

/* Function to print a string in rot 13 */
int customPrintRot13String(va_list argList, char outputBuffer[],
    int formatFlags, int outputWidth, int outputPrecision, int outputSize);
/* Width handler */
int writeChar(char c, char buffer[],
	int flags, int width, int precision, int size);
int writeNumber(int isNegative, int ind, char buffer[],
	int flags, int width, int precision, int size);
int writeNum(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char paddingChar, char extraChar);
    int writePointer(char buffer[], int startIndex, int length,
    int width, int flags, char paddingChar, char extraChar, int paddingStart);
int writeUnsigned(int isNegative, int ind,
    char buffer[], int flags, int width, int precision, int size);
    /*Utils*/
int appendHexaCode(char asciiCode, char buffer[], int index); 
long int convertSizeNumber(long int num, int size);
long int convertSizeUnsigned(unsigned long int num, int size);
int isDigit(char c);
int isPrintable(char c);
#endif /* MAIN_H */