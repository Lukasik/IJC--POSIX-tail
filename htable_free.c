/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

void htable_free(htable* t)
{
	htable_clear(t);
	free(t);
}