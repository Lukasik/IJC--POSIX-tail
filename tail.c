/*
* IJC-DU2, příklad 1a, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define BUFFSIZE 100

typedef struct list
{
	char* string;
	struct list* next;
} list;

int tail(int numLines, FILE* f)
{
	int singleChar;

	if(numLines < 0)
	{
		//tisk řádků od konce
		int buffsize = BUFFSIZE;
		int charsRead = 0;
		int terminated = 0;
		char* buffer = (char*) malloc(buffsize);
		list *l, *prev, *stop;
		stop = NULL;
		numLines *= -1;
		if(buffer == NULL)
		{
			return -1;
		}

		//inicializace lineárního seznamu
		stop = (list*) malloc(sizeof(list));
		if(stop == NULL)
		{
			free(buffer);
			return -1;
		}
		stop->string = NULL;
		l = prev = stop ;

		for(int i = 1; i < numLines; ++i)
		{
			l = (list*) malloc(sizeof(list));
			if(l == NULL)
			{
				l = stop;
				while(l != NULL)
				{
					prev = l;
					l = l->next;
					free(prev);
				}
				free(buffer);
				return -1;
			}
			l->string = NULL;
			prev->next = l;
			prev = l;
		}

		prev->next = stop;


		//čtení
		while((singleChar = fgetc(f)) != EOF)
		{
			terminated = 0;
			buffer[charsRead++] = singleChar;

			//konec řádku
			if(singleChar == '\n')
			{
				buffer[charsRead] = '\0';
				l->string = (char*) realloc(l->string, strlen(buffer)+1);
				if(l->string == NULL)
				{
					l = stop;
					while(l != NULL)
					{
						prev = l;
						l = l->next;
						free(prev->string);
						free(prev);
					}
					free(buffer);
					return -1;
				}
				strcpy(l->string, buffer);
				terminated = 1;
				stop = l;
				l = l->next;
				charsRead = 0;
				continue;
			}

			//zvětšení bufferu
			if(charsRead+2 == buffsize)
			{
				buffsize += BUFFSIZE;
				buffer = (char*) realloc(buffer, buffsize);
				if(buffer == NULL)
				{
					l = stop;
					while(l != NULL)
					{
						prev = l;
						l = l->next;
						free(prev->string);
						free(prev);
					}
					return -1;
				}
			}
		}

		//neukončený poslední řádek
		if(terminated == 0 && charsRead > 0)
		{
			buffer[charsRead] = '\0';
			l->string = (char*) realloc(l->string, strlen(buffer)+1);
			if(l->string == NULL)
			{
				l = stop;
				while(l != NULL)
				{
					prev = l;
					l = l->next;
					free(prev->string);
					free(prev);
				}
				free(buffer);
				return -1;
			}
			strcpy(l->string, buffer);
			stop = l;
			l = l->next;
		}

		free(buffer);

		//tisk výsledku
		while(numLines-- > 0)
		{
			//přeskočení neinicializovaných prvků seznamu (tisk více řádků než má soubor)
			if(l->string != NULL && strlen(l->string) != 0)
			{
				printf("%s", l->string);
			}
			prev = l;
			l = l->next;
			free(prev->string);
			free(prev);
		}

	}
	else
	{
		//tisk od řádku
		while((singleChar = fgetc(f)) != EOF)
		{
			if(numLines <= 1)
			{
				putc(singleChar, stdout);
			}

			if(singleChar == '\n')
			{
				--numLines;
			}
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	int numLines = -10;
	int res, n = 1;
	char* endptr;
	FILE* f = stdin;

	if(argc > 4)
	{	//moc parametrů
		fprintf(stderr, "Neplatný počet parametrů\n");
		return EXIT_FAILURE;
	}
	else if(argc == 2)
	{	//zadán pouze soubor
		f = fopen(argv[1], "r");
	}
	else if(argc > 2)
	{
		if(argc == 4)
		{	//počet řádků i se souborem, zkouším jestli je soubor zadán jako 1. nebo 3. parametr
			f = fopen(argv[3], "r");
			if(f == NULL)
			{
				n = 2;
				f = fopen(argv[1], "r");
			}
		}

		numLines = (int) strtod(argv[n+1], &endptr)*(-1);
		if(strcmp(argv[n], "-n") != 0 || *endptr != '\0')
		{
			fprintf(stderr, "Neplatné parametry\n");
			fclose(f);
			return EXIT_FAILURE;
		}

		if(*argv[n+1] == '+' || *argv[n+1] == '-')
		{
			numLines *= -1;
		}

		if(numLines == 0)
		{
			fclose(f);
			return EXIT_SUCCESS;
		}
	}

	if(f == NULL)
	{
		fprintf(stderr, "Soubor se nepodařilo otevřít\n");
		return EXIT_FAILURE;
	}

	res = tail(numLines, f);

	if(res != 0)
	{
		fprintf(stderr, "Došlo k chybě při čtení/nedostatek paměti\n");
		return EXIT_FAILURE;
	}

	fclose(f);
	return EXIT_SUCCESS;
}