#include "tetris.h"

time_t	gettime_as_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time_t)(time.tv_sec * 1000000 + time.tv_usec));
}
