/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

unsigned int hash_function(const char *str, unsigned int htable_size)
{
	unsigned int h=0;
	unsigned char *p;

	for(p=(unsigned char*)str; *p!='\0'; p++)
	{
		h = 31*h + *p;
	}

	return h % htable_size;
}