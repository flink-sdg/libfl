#include <stddef.h>

#ifndef FLBITS_H
#define FLBITS_H

typedef enum {
	BIG,
	LITTLE
} Endian;

void flbits_rotl_char(char*, size_t);
void flbits_rotr_char(char*, size_t);
void flbits_rotl_int(int*, size_t);
void flbits_rotr_int(int*, size_t);
void flbits_rotl_size_t(size_t*, size_t);
void flbits_rotr_size_t(size_t*, size_t);

void flbits_bprint_char(char);
void flbits_bprint_int(int);
void flbits_bprint_size_t(size_t);

Endian flbits_endian(void);
void flbits_eprint(void);

#endif
