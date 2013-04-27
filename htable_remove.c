/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

void htable_remove(htable* t, const char* key)
{
	int index = hash_function(key, t->size);
	htable_listitem* l = t->array[index];
	htable_listitem** prev = &(t->array[index]);

	while(l != NULL)
	{
		if(strcmp(key, l->key) == 0)
		{
			*prev = l->next;
			free(l);
			break;
		}

		prev = &l->next;
		l = l->next;
	}
}