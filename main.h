#ifndef main_h
#define main_h

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int _strlen(char * str);
int specifiercode(char c);
int * _charcode(char * str);
char * insertstr(char * str, int start, char * strvar);
char * _chartostring(char c);
int _printf(char * format, ...);

#endif /* main_h */
