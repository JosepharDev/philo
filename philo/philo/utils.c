#include "philo.h"

long set_time(void)
{
	struct timeval tp;
	long time;
	gettimeofday(&tp, NULL);
	// printf("%ld tv_sec\n", tp.tv_sec);
	// printf("%d tv_usec\n", tp.tv_usec);
	time = ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
	// printf("%ld tv_sec\n", tp.tv_sec * 1000);
	// printf("%d tv_usec\n", tp.tv_usec / 1000);
	return (time);
}

void ft_time(int num)
{
	// printf("%ld\n", set_time());
	long time;
	time = set_time();
	while(set_time() - time < num)
		usleep(10);
}
