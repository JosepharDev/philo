#include "philo.h"
void ft_print(t_philo philo, char *str)
{
	pthread_mutex_lock(philo.mutex_print);
	printf("%ld philosopher number %d %s\n", set_time() - philo.start_time, philo.index, str);
	pthread_mutex_unlock(philo.mutex_print);
}

void *func(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;

	while(true)
	{
		if(philo->index % 2 == 0)
		{
			pthread_mutex_lock(philo->forks);
			pthread_mutex_lock(philo->next_fork);
		}
		else
		{
			pthread_mutex_lock(philo->next_fork);
			pthread_mutex_lock(philo->forks);
		}
		ft_print(*philo, FORK);
		ft_print(*philo, EAT);

		// pthread_mutex_lock(&philo->all->lock);
		if (philo->num.ntpe > 0)
			philo->num_of_eating++;
		philo->last_eat = set_time();
		// pthread_mutex_unlock(&philo->all->lock);
		ft_time(philo->num.time_to_eat);

		pthread_mutex_unlock(philo->forks);
		pthread_mutex_unlock(philo->next_fork);

		ft_print(*philo, SLEEP);
		ft_time(philo->num.time_to_sleep);

		// pthread_mutex_lock(&philo->all->lock);
		// if(philo->num_of_eating == philo->num.ntpe)
		// {
		// 	// pthread_mutex_lock(philo->mutex_print);
		// 	// usleep(100000);
		// 	return (NULL);
		// }
		// pthread_mutex_unlock(&philo->all->lock);

		ft_print(*philo, THINK);
		// pthread_mutex_unlock(&philo->all->lock);

	}
	return NULL;
}

// void *ft_check(void *p)
// {
// 	t_all *all= (t_all *)p;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
	
// 	while(true)
// 	{
// 		while(i < all->num.num_philo)
// 		{
// 			// pthread_mutex_lock(&all->lock);
// 			if (all->philo[i].num_of_eating != all->num.ntpe)
// 			{
// 				if ((set_time() - all->philo[i].last_eat) >= all->num.time_to_die)
// 				{
// 					// write(2, "philo die", 10);
// 					ft_print(all->philo[i], DIE);
// 					pthread_mutex_lock(all->philo[i].mutex_print);
// 					// pthread_mutex_unlock(all->philo[i].forks);
// 					// pthread_mutex_unlock(all->philo[i].next_fork);
// 					// printf(" %d \n", all->philo[i].index);
// 					// printf("last time %ld time %ld res %ld time to die %d\n", all->philo[i].last_eat, set_time(), set_time() - all->philo[i].last_eat, all->num.time_to_die);
// 					// pthread_mutex_unlock(all->philo->mutex_print);
// 					return NULL;
// 				}
// 			}
// 			else
// 				j++;
// 			// pthread_mutex_unlock(&all->lock);
// 			if (j == all->num.num_philo)
// 					return (NULL);
// 			i++;
// 		}
// 		j = 0;
// 		i = 0;
// 	}
// 	return (NULL);
// }


static int	check_n(long n, t_philo *philo, int i)
{
	if (n >= philo[i].num.time_to_die)
	{
		pthread_mutex_lock(philo[i].mutex_print);
		printf("%ld philo number %d %s\n",
			set_time() - philo[i].start_time, philo[i].index, "die");
 printf("last time %ld time %ld res %ld time to die %d\n", philo[i].last_eat, set_time(), set_time() - philo[i].last_eat, philo[i].num.time_to_die);

		// printf("hell\n\n\n\n\n\nsf§d;j;gg;dj\n");
		
		return (0);
	}
	return (1);
}

void	*ft_checker(void *data)
{
	t_philo	*philo;
	long	n;
	int		i;
	int		eating;

	philo = (t_philo *)data;
	while (true)
	{
		i = 0;
		eating = 0;
		while (i < philo->num.num_philo)
		{
			n = set_time() - philo[i].last_eat;
			if (!check_n(n, philo, i))
				return (0);
			eating += (philo[i].num.ntpe > 0
					&& philo[i].num_of_eating >= philo[i].num.ntpe);
			i++;
		}
		if (eating == philo->num.num_philo)
			break ;
		// printf("hell\n\n\n\n\n\nsf§d;j;gg;dj\n");
		// printf("%d %d", eating, philo->num.num_philo);
	}
	return (NULL);
}
int ft_check_die(t_all *all)
{
	pthread_t check;
	pthread_create(&check, NULL, ft_checker, all->philo);
	pthread_join(check, NULL);
	return (0);
}

