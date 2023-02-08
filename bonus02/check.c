#include "philo.h"

int	check_die(long n, t_all *all)
{
	if (all->last_eat == -1)
		return (1);
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
	int		i;
	int		eating;

	all = (t_all *)data;
	while (true)
	{
		i = 0;
		eating = 0;
		sem_wait(all->sem_lock);
		while (i < all->philo.num_of_philo)
		{
			n = set_time() - all->last_eat;
			if (check_die(n, all) == 0)
			{
				sem_post(all->sem_lock);
				exit(1);
			}
			eating += (all->philo.ntpe > 0
					&& all->num_of_eating >= all->philo.ntpe);
			i++;
		}
		if (eating == all->philo.num_of_philo)
		{
			sem_post(all->sem_lock);
			exit(0);
		}
		sem_post(all->sem_lock);
	}
	return (NULL);
}