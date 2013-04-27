/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

void htable_clear(htable* t)
{
	htable_listitem *l, *lt;
	for(unsigned int i = 0; i < t->size; ++i)
	{
		l = t->array[i];

		while(l != NULL)
		{
			lt = l;
			l = l->next;
			free(lt->key);
			free(lt);
		}

		t->array[i] = NULL;
	}
}