/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:58:43 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/07 15:16:13 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo philo, char *str)
{
	pthread_mutex_lock(philo.mutex_print);
	printf("%ld philosopher number %d %s\n",
		set_time() - philo.start_time, philo.index, str);
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
