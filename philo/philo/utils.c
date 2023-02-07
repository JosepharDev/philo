/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:14:44 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/07 17:15:26 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	set_time(void)
{
	struct timeval	tp;
	long			time;

	gettimeofday(&tp, NULL);
	time = ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
	return (time);
}

void	ft_time(int num)
{
	long	time;

	time = set_time();
	while (set_time() - time < num)
		usleep(1000);
}
