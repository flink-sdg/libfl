#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flarr.h"



/*
 *	Create and clean up flarrs.
 */



flarr* flarr_new(size_t item_size)
{
	size_t items_size = 5;
	void *items = calloc(items_size, item_size);

	flarr *flarray = calloc(1, sizeof(flarr));

	flarray->items = items;
	flarray->item_size = item_size;
	flarray->items_count = 0;
	flarray->items_size = items_size;

	return flarray;
}

void flarr_clean(flarr *flarray)
{
	free(flarray->items);
	free(flarray);
}


/*
 *	Internally used to resize flarr->items.  If flarr->items_count == flarr->items_size, double flarr->items_size.
 */



void flarr_resize(flarr *flarray)
{
	if(flarray->items_count == flarray->items_size)
	{
		void *items = calloc(flarray->items_size * 2, flarray->item_size);
		memcpy(items, flarray->items, flarray->items_count * flarray->item_size);
		free(flarray->items);
		flarray->items = items;
		flarray->items_size *= 2;
	}
}



/*
 *	Various functions to append an item onto flarr->items.  Uses flarr_resize function.
 */



#define FLARR_APPEND(n, pd, c, p) \
void n(flarr *flarray, pd) \
{ \
	flarr_resize(flarray); \
\
	((c)flarray->items)[flarray->items_count] = p; \
	++flarray->items_count; \
} \

FLARR_APPEND(flarr_append, void *item, void **, item)
FLARR_APPEND(flarr_append_char, char c, char *, c)
FLARR_APPEND(flarr_append_int, int i, int *, i)
FLARR_APPEND(flarr_append_size_t, size_t s, size_t *, s)

void flarr_append_str(flarr* flarray, char* c)
{
	size_t clen = strlen(c);
	if(flarray->items_count + clen + 1 > flarray->items_size)
	{
		void *items = calloc(flarray->items_size + 2 * clen + 1, flarray->item_size);
		memcpy(items, flarray->items, flarray->items_count * flarray->item_size);
		free(flarray->items);
		flarray->items = items;
		flarray->items_size += 2 * clen;
	}

	strcpy(&((char *)flarray->items)[flarray->items_count], c);
	flarray->items_count += clen;
}



/*
 *	Various functions to set the value of flarr->items at a given index.
 */



#define FLARR_SET(n, pd, c, p) \
void n(flarr *flarray, size_t index, pd) \
{ \
	((c)flarray->items)[index] = p; \
} \

FLARR_SET(flarr_set, void *item, void **, item)
FLARR_SET(flarr_set_char, char c, char *, c)
FLARR_SET(flarr_set_int, int i, int *, i)
FLARR_SET(flarr_set_size_t, size_t s, size_t *, s)

void flarr_set_str(flarr *flarray, char *c)
{
	size_t clen = strlen(c);
	free(flarray->items);
	flarray->items = malloc((clen + 1) * sizeof(char));
	strcpy(flarray->items, c);

	flarray->items_count = clen;
	flarray->items_size = clen + 1;
}



/*
 *	Varios functions to get the value of flarr->items at a given index.  If index is out of range, a zero item is returned.
 */



#define FLARR_GET(r, n, f, c) \
r n(flarr *flarray, size_t index) \
{ \
	if(index >= flarray->items_count) return f; \
\
	return ((c)flarray->items)[index]; \
} \

FLARR_GET(void*, flarr_get, NULL, void **)
FLARR_GET(char, flarr_get_char, 0, char *)
FLARR_GET(int, flarr_get_int, 0, int *)
FLARR_GET(size_t, flarr_get_size_t, 0, size_t *)

char* flarr_get_str(flarr *flarray)
{
	return (char *)flarray->items;
}



/*
 * Various functions to reverse flarrays.
 */



#define FLARR_REVERSE(n, c) \
void n(flarr *flarray) \
{ \
	void *temp = malloc(flarray->items_count * flarray->item_size); \
\
	for(size_t i = 0; i < flarray->items_count; ++i) \
	{ \
		((c)temp)[i] = ((c)flarray->items)[flarray->items_count - (1 + i)]; \
	} \
\
	free(flarray->items); \
	flarray->items = temp; \
	flarray->items_size = flarray->items_count; \
} \

FLARR_REVERSE(flarr_reverse, void **)
FLARR_REVERSE(flarr_reverse_char, char *)
FLARR_REVERSE(flarr_reverse_str, char *)
FLARR_REVERSE(flarr_reverse_int, int *)
FLARR_REVERSE(flarr_reverse_size_t, size_t *)



/*
 *	Various function to get a string representation of a flarr.
 */



#define FLARR_TO_STRING(n, r, t) char* n(flarr *flarray) \
{ \
	char *temp = malloc(5242880 * sizeof(char)); \
\
	sprintf(temp, "items: {"); \
\
	for(size_t i = 0; i < flarray->items_count; ++i) \
	{ \
		sprintf(temp + strlen(temp), r, ((t)flarray->items)[i]); \
	} \
\
	sprintf(temp + strlen(temp), "}\nitem_size: %ld\nitems_count: %ld\nitems_size: %ld\nitems_bytes: %ld", flarray->item_size, flarray->items_count, flarray->items_size, flarray->items_size * flarray->item_size); \
\
	char *string = calloc(strlen(temp) + 1, sizeof(char)); \
	strcpy(string, temp); \
	free(temp); \
\
	return string; \
} \

FLARR_TO_STRING(flarr_to_string_char, "%c ", char *)
FLARR_TO_STRING(flarr_to_string_int, "%d ", int *)
FLARR_TO_STRING(flarr_to_string_size_t, "%ld ", size_t *)

char* flarr_to_string(flarr *flarray)
{
	char *temp = malloc(5242880 * sizeof(char));

	sprintf(temp, "items: %p\nitem_size: %ld\nitems_count: %ld\nitems_size: %ld\nitems_bytes: %ld", flarray->items, flarray->item_size, flarray->items_count, flarray->items_size, flarray->items_size * flarray->item_size);

	char *string = calloc(strlen(temp) + 1, sizeof(char));
	strcpy(string, temp);
	free(temp);

	return string;
}

char* flarr_to_string_str(flarr *flarray)
{
	char *temp = malloc(5242880 * sizeof(char));

	sprintf(temp, "items: %s\nitem_size: %ld\nitems_count: %ld\nitems_size: %ld\nitems_bytes: %ld", (char *)flarray->items, flarray->item_size, flarray->items_count, flarray->items_size, flarray->items_size * flarray->item_size);

	char *string = calloc(strlen(temp) + 1, sizeof(char));
	strcpy(string, temp);
	free(temp);

	return string;
}



/*
 *	Various functions to print flarrs. 
 */



#define FLARR_PRINT(n, t) \
void n(flarr *flarray) \
{ \
	char *flarr_string = t(flarray); \
	printf("%s", flarr_string); \
	free(flarr_string); \
} \

FLARR_PRINT(flarr_print, flarr_to_string)
FLARR_PRINT(flarr_print_char, flarr_to_string_char)
FLARR_PRINT(flarr_print_str, flarr_to_string_str)
FLARR_PRINT(flarr_print_int, flarr_to_string_int)
FLARR_PRINT(flarr_print_size_t, flarr_to_string_size_t)
