#include <stdlib.h>
#include <stdio.h>

#include "flbits.h"
#include "flarr.h"

/*
 * Various functions for bit rotation.
 */

#define FLBITS_ROT(n, p, d1, d2) \
void n(p *dest, size_t by) \
{ \
	size_t c = by % (sizeof(p) * 8); \
	*dest = (*dest d1 c) | (*dest d2 ((sizeof(p) * 8) - c));\
}

FLBITS_ROT(flbits_rotl_char, char, <<, >>)
FLBITS_ROT(flbits_rotr_char, char, >>, <<)
FLBITS_ROT(flbits_rotl_int, int, <<, >>)
FLBITS_ROT(flbits_rotr_int, int, >>, <<)
FLBITS_ROT(flbits_rotl_size_t, size_t, <<, >>)
FLBITS_ROT(flbits_rotr_size_t, size_t, >>, <<)

/*
 * Various functions for printing binary.
 */

#define FLBITS_BPRINT(n, t) \
void n(t v) \
{ \
	flarr *flarray = flarr_new(sizeof(t)); \
	for(size_t i = 0; i < sizeof(t) * 8; ++i) \
	{ \
		flarr_append_str(flarray, (v >> i) & 1 ? "1": "0"); \
	} \
	flarr_reverse_str(flarray); \
	printf("%s", (char*)flarray->items); \
	free(flarray); \
}

FLBITS_BPRINT(flbits_bprint_char, char)
FLBITS_BPRINT(flbits_bprint_int, int)
FLBITS_BPRINT(flbits_bprint_size_t, size_t)

Endian flbits_endian(void)
{
	int i = 1;

	return *(char*)&i == 1 ? LITTLE: BIG;
}

void flbits_eprint(void)
{
	printf("%s", flbits_endian() == LITTLE ? "little": "big");
}
