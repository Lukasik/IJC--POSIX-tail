/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "io.h"

int fgetword(char* s, int max, FILE* f)
{
	int c;
	int charsRead = 0;
	int res;

	while(charsRead < (max-1) && (c = fgetc(f)) != EOF && !isspace(c))
	{
		s[charsRead++] = c;
	}

	s[charsRead] = '\0';

	if(c == EOF && charsRead == 0)
	{
		res = EOF;
	}
	else
	{
		if(!isspace(c))
		{
			while((c = fgetc(f)) != EOF && !isspace(c))
			{
				charsRead++;
			}
		}

		res = charsRead;

		while(isspace(c) && (c = fgetc(f)) != EOF);
		ungetc(c, f);
	}

	return res;
}