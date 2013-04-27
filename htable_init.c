/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

htable* htable_init(size_t size)
{
	htable* t;

	t = (htable*) malloc(sizeof(htable)+sizeof(t->array[0])*(size-1));
	t->size = size;

	for(unsigned int i = 0; i < t->size; ++i)
	{
		t->array[i] = NULL;
	}

	return t;
}