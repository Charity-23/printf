#include "main.h"

/**
 * _strlen - calculate the length of string
 * @str: string param
 * Return: struct containing the len & fstring count
 */

struct cformat _strlen(char * str)
{
	int len = 0;
	int specifierscount = 0;

	while (str[len] != '\0')
	{
		if(str[len] == '%' && str[len + 1] != ' ')
		{
			specifierscount++;
		}
		len++;
	}
	struct cformat lendesc;
	lendesc.len = len;
	lendesc.specifierscount = specifierscount;
	return (lendesc);
}

/**
 * _charcode - gets fcodes and their positions
 * @str: string to be searched
 * @count: number of fcodes
 *
 * Return: stuct containing fcodes and their positions
 */

struct fcode  _charcode(char * str, int count)
{
	int position = 0;
	struct fcode dcode;
	dcode.codes = malloc(sizeof(int) * count);
	dcode.specifiercodes = malloc(sizeof(char) * count);
	int insertPosition = 0;

	while (str[position] != '\0')
	{
		if(str[position] == '%')
		{
			if(str[position+1] != ' ')
			{
				dcode.codes[insertPosition] = position;
				dcode.specifiercodes[insertPosition] = str[position+1];
				insertPosition++;
			}
		}
		position++;
	}
	return (dcode);
}

/**
 * insertstr - inserts a substring into another string
 * @str: format string
 * @start: start positin for intsert
 * @strvar: string to be inserted
 *
 * Return: the new string from adding the two
 */

char * insertstr(char * str, int start, char * strvar)
{
	struct cformat strvarlen = _strlen(strvar);
	struct cformat strlen = _strlen(str);

	int charsize = strvarlen.len + strlen.len;
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

			for(; l < strvarlen.len; l++)
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

/**
 * _chartostring - convert char to string
 * @c: char variable to convert
 *
 * Return: the resultant string
 */

char * _chartostring(char c)
{
	char * str = malloc(sizeof(char));
	str[0] = (char) c;
	return(str);
}

/**
 * _printf - print formatted string
 * @format: string to be formated & printed
 *
 * Retrun: number of bytes printed
 */

int _printf(char * format, ...)
{
	struct cformat fdetails = _strlen(format);
	struct fcode dcode = _charcode(format, fdetails.specifierscount);
	int * codeptr = dcode.codes;
	char* str1;
	char str2;

	va_list ptr;
	va_start(ptr, format);
	for (int i = 0; i < fdetails.specifierscount; i++)
	{
		if(dcode.specifiercodes[i] == 's')
		{
			str1 = va_arg(ptr, char*);
		}
		else if(dcode.specifiercodes[i] == 'c')
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

	for(int j = 0; j < fdetails.specifierscount; j++)
	{
		if(dcode.specifiercodes[j] == 's' && !stringdone)
		{
			dcode = _charcode(newstr,fdetails.specifierscount);
			codeptr = dcode.codes;
			newstr = insertstr(newstr, *codeptr, str1);
			fdetails.specifierscount--;
			stringdone = 1;
		}
		if(dcode.specifiercodes[j] == 'c' && !chardone)
		{
			char * strarr = _chartostring(str2);
			codeptr = dcode.codes;
			newstr = insertstr(newstr, *(codeptr), strarr);
			fdetails.specifierscount--;
			chardone = 1;
		}
		if(dcode.specifiercodes[j] == '%' && !percentdone)
		{
			char * str3 = "%";

			dcode = _charcode(newstr,fdetails.specifierscount);
			codeptr = dcode.codes;
			newstr = insertstr(newstr, *(codeptr), str3);
			fdetails.specifierscount--;
			percentdone = 1;
		}
	}
	struct cformat newstrlen = _strlen(newstr);
	write(2, newstr, newstrlen.len);
	return (newstrlen.len);
}



