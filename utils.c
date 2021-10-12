#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// printf("time %lu\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
