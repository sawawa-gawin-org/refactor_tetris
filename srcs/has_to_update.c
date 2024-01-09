#include "../tetris.h"

//hasToUpdate
int	has_to_update(suseconds_t g_interval)
{
	suseconds_t		now_time_us;
	suseconds_t		pre_time_us;

	now_time_us = (suseconds_t)(g_now_time.tv_sec * 1000000 + g_now_time.tv_usec);
	pre_time_us = (suseconds_t)(g_pre_time.tv_sec * 1000000 + g_pre_time.tv_usec);
	if (now_time_us - pre_time_us > g_interval)
		return (TRUE);
	else
		return (FALSE);
}
