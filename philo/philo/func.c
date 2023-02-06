#include "philo.h"
void ft_print(t_philo philo, char *str)
{
	pthread_mutex_lock(philo.mutex_print);
	printf("%ld philosopher number %d %s\n", set_time() - philo.start_time, philo.index, str);
	pthread_mutex_unlock(philo.mutex_print);
}
void	philo_eat(t_philo *philo)
{
	ft_print(*philo, EAT);
	pthread_mutex_lock(&philo->all->lock);
	philo->last_eat = set_time();
	if (philo->num.ntpe > 0)
			philo->num_of_eating++;
	pthread_mutex_unlock(&philo->all->lock);
	ft_time(philo->num.time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	ft_print(*philo, SLEEP);
	ft_time(philo->num.time_to_sleep);
}

void	philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->forks);
	ft_print(*philo, FORK);
	pthread_mutex_lock(philo->next_fork);
	ft_print(*philo, FORK);
}

void *func(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	if(philo->index % 2 == 0)
		ft_time(100);
	while(1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		pthread_mutex_unlock(philo->forks);
		pthread_mutex_unlock(philo->next_fork);

		pthread_mutex_lock(&philo->all->lock);
		if(philo->num_of_eating == philo->num.ntpe)
		{
			philo->last_eat = -1;
			pthread_mutex_unlock(&philo->all->lock);

			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->lock);
		
		philo_sleep(philo);
		ft_print(*philo, THINK);
	}
	return NULL;
}

static int	check_n(long n, t_philo *philo, int i)
{
	if(philo[i].last_eat == -1)
		return 1;
	pthread_mutex_lock(philo[i].mutex_print);
	if (n >= philo[i].num.time_to_die)
	{
		printf("%ld philo number %d %s\n",
			set_time() - philo[i].start_time, philo[i].index, "die");
//  printf("last time %ld time %ld res %ld time to die %d\n", philo[i].last_eat, set_time(), set_time() - philo[i].last_eat, philo[i].num.time_to_die);
		// pthread_mutex_lock(philo[i].mutex_print);
		return (0);
	}
	pthread_mutex_unlock(philo[i].mutex_print);
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
		pthread_mutex_lock(&philo->all->lock);
		while (i < philo->num.num_philo)
		{
			// ft_time(100);
			n = set_time() - philo[i].last_eat;
			if (check_n(n, philo, i) == 0)
			{
				pthread_mutex_unlock(&philo->all->lock);
				return (0);
			}
			eating += (philo[i].num.ntpe > 0
					&& philo[i].num_of_eating >= philo[i].num.ntpe);
			i++;
		}
		if (eating == philo->num.num_philo)
		{
			pthread_mutex_unlock(&philo->all->lock);
			return (NULL) ;
		}
		pthread_mutex_unlock(&philo->all->lock);
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

