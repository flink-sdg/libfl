#include "./flarr/flarr.h"
#include "./fldict/fldict.h"
#include "./flutil/flutil.h"

int main(void)
{
	flarr_hello(FLARR_CONST);
	fldict_hello(FLDICT_CONST);
	flutil_hello(FLUTIL_CONST);

	return 0;
}
