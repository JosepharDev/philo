/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:07:12 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/08 14:30:33 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_create(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->num.num_philo)
	{
		if (pthread_create(&all->philo[i].philo, NULL,
				&func, &all->philo[i]) != 0)
		{
			printf("Error in pthread_create");
			return (-1);
		}
		pthread_detach(all->philo[i].philo);
		i++;
	}
	if (supervis(all) == 1)
		return (-1);
	return (0);
}

void	ft_free(t_all *all)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&all->lock);
	while (i < all->num.num_philo)
	{
		pthread_mutex_destroy(&all->philo->forks[i++]);
	}
	free(all->forks);
}

int	main(int ac, char **av)
{
	t_all	all;

	if (ac == 5 || ac == 6)
	{
		if (ft_init(&all, av) == -1)
		{
			return (-1);
		}
		if (thread_create(&all) == -1)
		{
			return (1);
		}
		ft_free(&all);
	}
	else
		printf("Invalid Argemment\n");
	return (0);
}
