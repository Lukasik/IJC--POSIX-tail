/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

void htable_foreach(htable* t, void (*function)(htable_listitem*))
{
	htable_listitem *l;
	for(unsigned int i = 0; i < t->size; ++i)
	{
		l = t->array[i];

		while(l != NULL)
		{
			function(l);
			l = l->next;
		}
	}
}