#include <stdlib.h>

#include "fldict.h"
#include "flarr.h"

fldict* fldict_new(void)
{
	fldict *fldictionary = calloc(1, sizeof(fldict));

	fldictionary->fldict_indicies = flarr_new(sizeof(void*));
	fldictionary->keys = flarr_new(sizeof(char*));
	fldictionary->key_count = 0;
	fldictionary->duplicate_hash_count = 0;

	return fldictionary;
}

void fldict_clean(fldict* fldictionary)
{
	free(fldictionary->fldict_indicies);
	free(fldictionary->keys);
	free(fldictionary);
}

void fldict_set(char*, void*);
void fldict_set_flarr(char*, flarr*);
void fldict_set_str(char*, char*);
void fldict_set_int(char*, int);
void fldict_set_size_t(char*, size_t);

void* fldict_get(char*);
flarr* fldict_get_flarr(char*);
char* fldict_get_str(char*);
int fldict_get_int(char*);
size_t fldict_get_size_t(char*);
