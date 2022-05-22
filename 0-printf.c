#include "./test/main.h"

/**
 * _printf - prints output to standard output
 * base on a format.
 * @format: the format of the string to print
 *
 * Return: number of characters printed except
 * null byte
 */

int specifierscount = 0;
char * specifiercodes;

int _printf(const char *format, ...)
{
	_strlen(format);
	int * codeptr = _charcode(format);
	char* str1;
        char str2;

	va_list ptr;
	va_start(ptr, format);
	for (int i = 0; i < specifierscount; i++)
	{
		if(specifiercodes[i] == 's')
		{
			str1 = va_arg(ptr, char*);
		}
		else if(specifiercodes[i] == 'c')
		{
			str2 = va_arg(ptr, int);
		}
		else
		{
			continue;
		}
	}
	va_end(ptr);

	char * newstr = format;
	int chardone = 0;
        int stringdone = 0;
	int percentdone = 0;

	for(int j = 0; j < specifierscount; j++)
	{
		if(specifiercodes[j] == 's' && !stringdone)
		{
			codeptr = _charcode(newstr);
			newstr = insertstr(newstr, *codeptr, str1);
			specifierscount--;
			stringdone = 1;
		}
		if(specifiercodes[j] == 'c' && !chardone)
		{
			char * strarr = _chartostring(str2);
			codeptr = _charcode(newstr);
			newstr = insertstr(newstr, *(codeptr), strarr);
			specifierscount--;
			chardone = 1;
		}
		if(specifiercodes[j] == '%' && !percentdone)
		{
			char * str3 = "%";

			codeptr = _charcode(newstr);
			newstr = insertstr(newstr, *(codeptr), str3);
			specifierscount--;
			percentdone = 1;
		}
	}

	write(2, newstr, _strlen(newstr));

	return (_strlen(newstr));
}

char * _chartostring(char c)
{
	char * str = malloc(sizeof(char));

	str[0] = (char) c;

	return(str);
}


char * insertstr(char * str, int start, char * strvar)
{
	int charsize = _strlen(strvar) + _strlen(str);
	static char * charmem;
	charmem = malloc(sizeof(char) * charsize);
	int i = 0;
	int l = 0;
	int pause = 0;

	for(;i < charsize; i++)
	{
		if(i == start)
		{
			pause = i;

			for(; l < _strlen(strvar); l++)
			{
				charmem[i] = strvar[l];
				i++;
			}
			pause += 2;
		}
		if(l != 0)
		{
			charmem[i] = str[pause];
			pause++;
		}
		else
		{
			charmem[i] = str[i];
		}
	}
	return (charmem);
}

int * _charcode(char * str)
{
	int position = 0;
	int * codes = malloc(sizeof(int) * specifierscount);
	specifiercodes = malloc(sizeof(char) * specifierscount);
	int insertPosition = 0;

	while (str[position] != '\0')
	{
		if(str[position] == '%')
		{
			if(str[position+1] != ' ')
			{
				codes[insertPosition] = position;
				specifiercodes[insertPosition] = str[position+1];
				insertPosition++;
			}
		}
		position++;
	}
	return (codes);
}

int _strlen(char * str)
{
	int len = 0;
	static int var[2];

	while (str[len] != '\0')
	{
		if(str[len] == '%' && str[len + 1] != ' ')
		{
			specifierscount++;
		}
		len++;
	}
	return (len);
}
