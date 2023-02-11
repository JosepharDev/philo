/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:55:56 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/10 17:17:59 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*func(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		pthread_mutex_unlock(philo->forks);
		pthread_mutex_unlock(philo->next_fork);
		pthread_mutex_lock(philo->lock);
		if (philo->num_of_eating == philo->num.ntpe)
		{
			philo->last_eat = -1;
			pthread_mutex_unlock(philo->lock);
			return (NULL);
		}
		pthread_mutex_unlock(philo->lock);
		philo_sleep(philo);
		ft_print(*philo, THINK);
	}
	return (NULL);
}

int	check_die(long n, t_philo *philo, int i, int *eating)
{
	n = set_time() - philo[i].last_eat;
	pthread_mutex_lock(philo->mutex_print);
	*eating = (*eating) + (philo[i].num.ntpe > 0
			&& philo[i].num_of_eating >= philo[i].num.ntpe);
	if (philo[i].last_eat == -1)
	{
		pthread_mutex_unlock(philo->mutex_print);
		return (1);
	}
	if (n >= philo[i].num.time_to_die)
	{
		printf("%ld philo number %d %s\n",
			set_time() - philo[i].start_time, philo[i].index, "die");
		return (0);
	}
	pthread_mutex_unlock(philo->mutex_print);
	return (1);
}

void	*ft_check(void *data)
{
	t_philo	*philo;
	int		i;
	int		eating;

	philo = (t_philo *)data;
	while (true)
	{
		i = -1;
		eating = 0;
		pthread_mutex_lock(philo->lock);
		while (++i < philo->num.num_philo)
		{
			if (check_die(0, philo, i, &eating) == 0 \
				&& pthread_mutex_unlock(philo->lock) != -7)
				return (0);
		}
		if (eating == philo->num.num_philo)
		{
			pthread_mutex_unlock(philo->lock);
			return (NULL);
		}
		pthread_mutex_unlock(philo->lock);
	}
	return (NULL);
}

int	supervis(t_all *all)
{
	pthread_t	check;

	if (pthread_create(&check, NULL, ft_check, all->philo) != 0)
	{
		printf("Error in pthread_create");
		return (-1);
	}
	if (pthread_join(check, NULL) != 0)
	{
		printf("Error in pthread_join");
		return (-1);
	}
	return (0);
}
