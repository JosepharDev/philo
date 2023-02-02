#include "philo.h"
void ft_print(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.mutex_print);
	printf("%ld philosopher number %d %s\n", set_time(), philo.index, str);
	pthread_mutex_unlock(&philo.mutex_print);
}

void *func(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;

	while(true)
	{
		pthread_mutex_lock(philo->forks);
		pthread_mutex_lock(philo->next_fork);
		ft_print(*philo, FORK);
		ft_print(*philo, EAT);
		if (philo->num.ntpe > 0)
			philo->num_of_eating++;
		philo->last_eat = set_time();
		ft_time(philo->num.time_to_eat);
		pthread_mutex_unlock(philo->forks);
		pthread_mutex_unlock(philo->next_fork);
		ft_print(*philo, SLEEP);
		ft_time(philo->num.time_to_sleep);
		ft_print(*philo, THINK);
	}
	return NULL;
}
int ft_check_die(t_all *all)
{
	int i;

	i = 0;
	while(true)
	{
		while(i < all->num.num_philo)
		{
			if ((all->philo[i].last_eat - set_time()) > all->num.time_to_die)
				write(2, "philo die", 10);
				return 1;
			i++;
		}
		i = 0;
	}
	write(2,"sdsd", 4);
	return (1);
}
