/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:02:21 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/08 14:21:37 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_all *all, pthread_mutex_t *mutex_print)
{
	int	i;

	i = 0;
	while (i < all->num.num_philo)
	{
		all->philo[i].forks = &all->forks[i];
		all->philo[i].next_fork = &all->forks[(i + 1) % all->num.num_philo];
		all->philo[i].num = all->num;
		all->philo[i].num_of_eating = 0;
		all->philo[i].start_time = set_time();
		all->philo[i].last_eat = set_time();
		all->philo[i].index = i + 1;
		all->philo[i].mutex_print = mutex_print;
		all->philo[i].all = all;
		i++;
	}
}

int	ft_init(t_all *all, char **av)
{
	int				i;
	pthread_mutex_t *mutex_print;

	i = 0;
	all->num.num_philo = ft_atol(av[1]);
	all->num.time_to_die = ft_atol(av[2]);
	all->num.time_to_eat = ft_atol(av[3]);
	all->num.time_to_sleep = ft_atol(av[4]);
	if (!av[5])
		all->num.ntpe = -1;
	else
	{
		all->num.ntpe = ft_atol(av[5]);
		if (all->num.ntpe <= 0)
		{
			printf("invalid arg\n");
			return (-1);
		}
	}
	if (all->num.num_philo < 0 || all->num.time_to_die < 0
		|| all->num.time_to_eat < 0 || all->num.time_to_sleep < 0)
	{
		printf("invalid arg\n");
		return (-1);
	}
	all->philo = malloc(sizeof(t_philo) * all->num.num_philo);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num.num_philo);
	mutex_print = malloc(sizeof(pthread_mutex_t) * 1);
	if (!all->philo || !all->forks || !mutex_print)
	{
		printf("allocation failure");
		return (-1);
	}
	while (i < all->num.num_philo)
	{
		if (pthread_mutex_init(&all->forks[i++], NULL) != 0)
			return (-1);
	}
	if (pthread_mutex_init(mutex_print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&all->lock, NULL) != 0)
		return (-1);
	init_philo(all, mutex_print);
	return (0);
}
