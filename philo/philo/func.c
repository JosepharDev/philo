/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:55:56 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/07 15:17:57 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->index % 2 == 0)
		ft_time(10);
	while (1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		pthread_mutex_unlock(philo->forks);
		pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_lock(&philo->all->lock);
		if (philo->num_of_eating == philo->num.ntpe)
		{
			philo->last_eat = -1;
			pthread_mutex_unlock(&philo->all->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->lock);
		philo_sleep(philo);
		ft_print(*philo, THINK);
	}
	return (NULL);
}

int	check_die(long n, t_philo *philo, int i)
{
	if (philo[i].last_eat == -1)
		return (1);
	pthread_mutex_lock(philo[i].mutex_print);
	if (n >= philo[i].num.time_to_die)
	{
		printf("%ld philo number %d %s\n",
			set_time() - philo[i].start_time, philo[i].index, "die");
		return (0);
	}
	pthread_mutex_unlock(philo[i].mutex_print);
	return (1);
}

void	*ft_check(void *data)
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
			n = set_time() - philo[i].last_eat;
			if (check_die(n, philo, i) == 0)
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
			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->lock);
	}
	return (NULL);
}

int	supervis(t_all *all)
{
	pthread_t	check;

	if (pthread_create(&check, NULL, ft_check, all->philo) == -1)
		return (-1);
	pthread_join(check, NULL);
	return (0);
}
