/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include "htable.h"

void htable_statistics(htable* t)
{
	unsigned int min = UINT_MAX;
	unsigned int max = 0;
	unsigned int sum = 0;
	unsigned int count = 0;
	htable_listitem* l;

	for(unsigned int i = 0; i < t->size; ++i)
	{
		count = 0;
		l = t->array[i];

		while(l != NULL)
		{
			++count;
			l = l->next;
		}

		sum += count;

		if(count > max)
		{
			max = count;
		}

		if(count < min)
		{
			min = count;
		}
	}

	printf("Min: %d\nMax: %d\nAvg: %lf\n", min, max, (double)sum/t->size);
}