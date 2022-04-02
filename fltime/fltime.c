#include <time.h>
#include <math.h>



/*
 * unix time seconds
 */



unsigned long long fltime_s(void)
{
	struct timespec fltimespec;
	timespec_get(&fltimespec, TIME_UTC);

	return fltimespec.tv_sec;
}



/*
 * unix time milliseconds
 */



unsigned long long fltime_ms(void)
{
	struct timespec fltimespec;
	timespec_get(&fltimespec, TIME_UTC);

	return fltimespec.tv_sec * 1000 + floor(fltimespec.tv_nsec / 1e+6);
}



/*
 * unix time nanoseconds
 */



unsigned long long fltime_ns(void)
{
	struct timespec fltimespec;
	timespec_get(&fltimespec, TIME_UTC);

	return fltimespec.tv_sec * 1e+9 + fltimespec.tv_nsec;
}
