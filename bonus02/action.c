#include "philo.h"

void	print(t_all *all, char *str)
{
	sem_wait(all->sem_print);
	printf("%ld philo number %d %s\n", set_time() - all->start_time, all->index, str);
	sem_post(all->sem_print);
}

void fork_eat(t_all *all)
{
	sem_wait(all->fork);
	print(all, FORK);
	sem_wait(all->fork);
	print(all, FORK);
	print(all, EAT);
	if (all->philo.ntpe > 0)
		all->num_of_eating++;
	all->last_eat = set_time();
	ft_time(all->philo.time_to_eat);
	sem_post(all->fork);
	sem_post(all->fork);
}

void	life_philo(t_all *all)
{
	if (all->index % 2 == 0)
		usleep(1000);
	while(1)
	{
		fork_eat(all);
		if (all->philo.ntpe == all->num_of_eating)
		{
			all->last_eat = -1;
			exit(0);
		}
		print(all, SLEEP);
		ft_time(all->philo.time_to_sleep);
		print(all, THINK);
	}
}