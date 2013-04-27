/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

htable_listitem* htable_lookup(htable* t, char* key)
{
	int index = hash_function(key, t->size);
	htable_listitem* l = t->array[index];
	htable_listitem** prev = &(t->array[index]);

	while(l != NULL)
	{
		if(strcmp(key, l->key) == 0)
		{
			return l;
		}

		prev = &(l->next);
		l = l->next;
	}

	htable_listitem* newL = (htable_listitem*) malloc(sizeof(htable_listitem));
	if(newL != NULL)
	{
		newL->key = (char*) malloc(sizeof(char)*(strlen(key)+1));
		if(newL->key == NULL)
		{
			free(newL);
			return NULL;
		}
		newL->key = strncpy(newL->key, key, strlen(key)+1);
		newL->next = NULL;
		*prev = newL;
	}

	return newL;
}