/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"
#include "io.h"

//255 + \0
#define WORDLIMIT 255

/*
	ideální hashovací tabulka - každý seznam má právě jeden prvek
	=> ve většině dokumentů jsou používána slova, které se týkají jednoho témata
	=> 2000 - počet slov "basic english" + 500 tématických
*/
#define HTABLESIZE 2500

//@todo: inline funkce

void dump(htable_listitem* l)
{
	printf("Key: %s, count: %d\n", l->key, l->data);
}

int main(void)
{
	int res, wordOverflow = 0;
	char s[WORDLIMIT];
	htable* t = htable_init(HTABLESIZE);
	htable_listitem* l;

	if(t == NULL)
	{
		fprintf(stderr, "Nejde alokovat paměť\n");
		htable_free(t);
		return EXIT_FAILURE;
	}

	while((res = fgetword(s, WORDLIMIT, stdin)) != EOF)
	{
		if(res > WORDLIMIT-1 && !wordOverflow)
		{
			wordOverflow = 1;
			fprintf(stderr, "Slovo přeteklo\n");
		}

		l = htable_lookup(t, s);

		if(l == NULL)
		{
			fprintf(stderr, "Nejde alokovat paměť\n");
			htable_free(t);
			return EXIT_FAILURE;
		}

		l->data++;
	}

	// htable_foreach(t, dump);
	htable_statistics(t);

	htable_free(t);
	return EXIT_SUCCESS;
}