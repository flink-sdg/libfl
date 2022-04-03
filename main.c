#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

#include "flarr.h"
#include "fldict.h"
#include "flutil.h"
#include "fltime.h"
#include "flbits.h"

#define N printf("\n");
#define NN printf("\n\n");

int main(void)
{
	flarr *flarray_int = flarr_new(sizeof(int));
	flarr *flarray_char = flarr_new(sizeof(char));
	flarr *flarray_str = flarr_new(sizeof(char));
	flarr *flarray_flarr = flarr_new(sizeof(flarr));

	flarr_append(flarray_flarr, flarray_int);
	flarr_append(flarray_flarr, flarray_char);
	flarr_append(flarray_flarr, flarray_str);

	time_t t, tb, te;
	srand((unsigned) time(&t));
	for(size_t i = 0; i < 70; ++i)
	{
		flarr_append_int(flarray_int, rand() % 50);
	}

	for(size_t i = 0; i < 365; ++i)
	{
		flarr_append_char(flarray_char, (rand() % 26) + 'a');
	}

	flarr_append_str(flarray_str, "12345");
	flarr_append_str(flarray_str, "6789012345");

	unsigned long long start_s = fltime_s(), start_ms = fltime_ms(), start_ns = fltime_ns();

	NN
	flarr_print(flarray_flarr);
	NN
	flarr_print_int(((flarr **)flarray_flarr->items)[0]);
	NN
	flarr_print_char(((flarr **)flarray_flarr->items)[1]);
	NN
	flarr_print_str(((flarr **)flarray_flarr->items)[2]);

	flarr_reverse(flarray_flarr);
	flarr_reverse_int(flarray_int);
	flarr_reverse_char(flarray_char);
	flarr_reverse_str(flarray_str);

	NN
	flarr_print(flarray_flarr);
	NN
	flarr_print_int(flarray_int);
	NN
	flarr_print_char(flarray_char);
	NN
	flarr_print_str(flarray_str);

	NN
	printf("RUN TIME:\n\n%lld seconds\n%lld milliseconds\n%lld nanoseconds", fltime_s() - start_s, fltime_ms() - start_ms, fltime_ns() - start_ns);

	for(size_t i = 0; i < flarray_flarr->items_count; ++i)
	{
		flarr_clean((flarr*)flarr_get(flarray_flarr, i));
	}

	flarr_clean(flarray_flarr);

	char cbits = 6;
	int ibits = 7;
	size_t sbits = 511;

	NN
	flbits_bprint_char(cbits);
	N
	flbits_rotl_char(&cbits, 4);	
	flbits_bprint_char(cbits);
	N
	flbits_rotr_char(&cbits, 6);
	flbits_bprint_char(cbits);
	
	NN
	flbits_bprint_int(ibits);
	N
	flbits_rotl_int(&ibits, 10);
	flbits_bprint_int(ibits);
	N
	flbits_rotr_int(&ibits, 8);
	flbits_bprint_int(ibits);

	NN
	flbits_bprint_size_t(sbits);
	N
	flbits_rotl_size_t(&sbits, 4);
	flbits_bprint_size_t(sbits);
	N
	flbits_rotr_size_t(&sbits, 8);
	flbits_bprint_size_t(sbits);

	NN
	flbits_eprint();
	N

	return 0;
}
