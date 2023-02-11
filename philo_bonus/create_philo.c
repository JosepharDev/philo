/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:09:05 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/10 11:14:50 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo(t_all *all)
{
	int			i;
	pthread_t	thread;

	i = -1;
	while (++i < all->philo.num_of_philo)
	{
		all->index = i + 1;
		all->pid[i] = fork();
		if (all->pid[i] == -1)
		{
			while (i >= 0)
				kill(all->pid[i--], SIGKILL);
			printf("Error in fork\n");
			exit(1);
		}
		else if (all->pid[i] == 0)
		{
			pthread_create(&thread, NULL, ft_check, all);
			pthread_detach(thread);
			life_philo(all);
			exit(0);
		}
	}
	return (0);
}
