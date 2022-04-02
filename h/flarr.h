#include <stddef.h>

#ifndef FLARR_H
#define FLARR_H

typedef struct {
	void *items;
	size_t item_size;
	size_t items_count;
	size_t items_size;
} flarr;

flarr* flarr_new(size_t);

void flarr_append(flarr*, void*);
void flarr_append_char(flarr*, char);
void flarr_append_int(flarr*, int);
void flarr_append_size_t(flarr*, size_t);
void flarr_append_str(flarr*, char*);

void flarr_set(flarr*, size_t, void*);
void flarr_set_char(flarr*, size_t, char);
void flarr_set_int(flarr*, size_t, int);
void flarr_set_size_t(flarr*, size_t, size_t);

void* flarr_get(flarr*, size_t);
char flarr_get_char(flarr*, size_t);
int flarr_get_int(flarr*, size_t);
size_t flarr_get_size_t(flarr*, size_t);
char* flarr_get_str(flarr*);

void flarr_reverse(flarr*);
void flarr_reverse_char(flarr*);
void flarr_reverse_str(flarr*);
void flarr_reverse_int(flarr*);
void flarr_reverse_size_t(flarr*);

char* flarr_to_string_char(flarr*);
char* flarr_to_string_int(flarr*);
char* flarr_to_string_size_t(flarr*);
char* flarr_to_string(flarr*);
char* flarr_to_string_str(flarr*);

void flarr_print(flarr*);
void flarr_print_char(flarr*);
void flarr_print_str(flarr*);
void flarr_print_int(flarr*);
void flarr_print_size_t(flarr*);

#endif
