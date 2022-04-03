#include <stddef.h>

#include "flarr.h"

#ifndef FLDICT_H
#define FLDICT_H

typedef struct fldict_index {
	char *key;
	void *val;
	struct fldict_index *next;
} fldict_index;

typedef struct {
	flarr *fldict_indicies;
	flarr *keys;
	size_t key_count;
	size_t duplicate_hash_count;
} fldict;

fldict* fldict_new(void);
void fldict_clean(fldict*);

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

#endif
