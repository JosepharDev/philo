#include "philo.h"
void ft_print(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.mutex_print);
	printf("%ld philosopher number %d %s\n", set_time() - philo.start_time, philo.index, str);
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
		pthread_mutex_lock(&philo->all->lock);
		if (philo->num.ntpe > 0)
			philo->num_of_eating++;
		philo->last_eat = set_time();
		pthread_mutex_unlock(&philo->all->lock);
		ft_time(philo->num.time_to_eat);
		pthread_mutex_unlock(philo->forks);
		pthread_mutex_unlock(philo->next_fork);
		ft_print(*philo, SLEEP);
		ft_time(philo->num.time_to_sleep);
		pthread_mutex_lock(&philo->all->lock);
		if(philo->num_of_eating == philo->num.ntpe)
			return (NULL);
		pthread_mutex_unlock(&philo->all->lock);
		ft_print(*philo, THINK);
		// pthread_mutex_unlock(&philo->all->lock);

	}
	return NULL;
}

void *ft_check(void *p)
{
	t_all *all= (t_all *)p;
	int i;
	int j;

	i = 0;
	j = 0;
	
	while(true)
	{
		while(i < all->num.num_philo)
		{
			pthread_mutex_lock(&all->lock);
			if (all->philo[i].num_of_eating != all->num.ntpe)
			{
				if ((set_time() - all->philo[i].last_eat) >= all->num.time_to_die)
				{
					pthread_mutex_lock(&all->philo->mutex_print);
					write(2, "philo die", 10);
					printf(" %d \n", all->philo[i].index);
					printf("last time %ld time %ld res %ld time to die %d\n", all->philo[i].last_eat, set_time(), set_time() - all->philo[i].last_eat, all->num.time_to_die);
					return NULL;
				}
			}
			else
				j++;
			pthread_mutex_unlock(&all->lock);
			if (j == all->num.num_philo)
					return (NULL);
			i++;
		}
		j = 0;
		i = 0;
	}
	return (NULL);
}
int ft_check_die(t_all *all)
{
	pthread_t check;
	pthread_create(&check, NULL, ft_check, all);
	pthread_join(check, NULL);
	return (0);
}

