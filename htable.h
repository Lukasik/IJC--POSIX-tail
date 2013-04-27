/*
* IJC-DU2, příklad 2, 20.4.2013
* Autor: Lukáš Vokráčko, FIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

typedef struct htable_listitem htable_listitem;

struct htable_listitem
{
	char* key;
	unsigned int data;
	htable_listitem *next;
};

typedef struct
{
	unsigned int size;
	htable_listitem* array[1];
} htable;

htable* htable_init(size_t size);

//inline (musely by být definovány v hlavičce != "V knihovně musí být každá funkce ve zvláštním modulu")
htable_listitem* htable_lookup(htable* t, char* key);
unsigned int hash_function(const char *str, unsigned int htable_size);

void htable_clear(htable* t);
void htable_foreach(htable* t, void (*function)(htable_listitem*));
void htable_free(htable* t);
void htable_remove(htable* t, const char* key);
void htable_statistics(htable* t);

void dump(htable_listitem* l);