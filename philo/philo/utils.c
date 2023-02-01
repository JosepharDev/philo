#include "philo.h"

void set_time(void)
{
	struct timeval tp;
	if (gettimeofday(tp, NULL) != 0)
		return ;
}