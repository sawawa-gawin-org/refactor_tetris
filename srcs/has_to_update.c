#include "../tetris.h"

//hasToUpdate
int	has_to_update(suseconds_t timer)
{
	suseconds_t		now_time_us;
	suseconds_t		pre_time_us;

	now_time_us = (suseconds_t)(now_time.tv_sec * 1000000 + now_time.tv_usec);
	pre_time_us = (suseconds_t)(pre_time.tv_sec * 1000000 + pre_time.tv_usec);
	if (now_time_us - pre_time_us > timer)
		return (TRUE);
	else
		return (FALSE);
}
