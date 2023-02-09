#include "philo.h"

int	check_die(long n, t_all *all)
{
	sem_wait(all->sem_print);
	if (n >= all->philo.time_to_die)
	{
		printf("%ld philo number %d %s\n",
			set_time() - all->start_time, all->index, "die");
		return (0);
	}
	sem_post(all->sem_print);
	return (1);
}

void	*ft_check(void *data)
{
	t_all *all;
	long	n;

	all = (t_all *)data;
	while (true)
	{
		n = set_time() - ((all->last_eat.tv_sec * 1000)
			+ (all->last_eat.tv_usec / 1000));
		if (check_die(n, all) == 0)
			exit(1);
	}
	return (NULL);
}