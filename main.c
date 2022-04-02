#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

#include "flarr.h"
#include "fldict.h"
#include "flutil.h"
#include "fltime.h"

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

	flarr_print(flarray_flarr);
	flarr_print_int(((flarr **)flarray_flarr->items)[0]);
	flarr_print_char(((flarr **)flarray_flarr->items)[1]);
	flarr_print_str(((flarr **)flarray_flarr->items)[2]);

	flarr_reverse(flarray_flarr);
	flarr_reverse_int(flarray_int);
	flarr_reverse_char(flarray_char);
	flarr_reverse_str(flarray_str);

	flarr_print(flarray_flarr);
	flarr_print_int(flarray_int);
	flarr_print_char(flarray_char);
	flarr_print_str(flarray_str);
	
	printf("RUN TIME:\n\n%lld seconds\n%lld milliseconds\n%lld nanoseconds", fltime_s() - start_s, fltime_ms() - start_ms, fltime_ns() - start_ns);

	free(flarray_flarr);
	free(flarray_str);
	free(flarray_char);
	free(flarray_int);

	return 0;
}
