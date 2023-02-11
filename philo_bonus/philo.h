/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:09:19 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/10 15:33:57 by yoyahya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FORK "has taken a fork"

typedef struct s_philo
{
	long	num_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	ntpe;
}t_philo;

typedef struct s_all
{
	int				index;
	int				num_of_eating;
	struct timeval	last_eat;
	long			start_time;
	sem_t			*fork;
	sem_t			*sem_print;
	sem_t			*sem_lock;
	t_philo			philo;
	pid_t			*pid;
}t_all;

int		init_struct(t_all *all, char **av);
int		init_philo(t_all *all);
void	print(t_all *all, char *str);
void	fork_eat(t_all *all);
void	life_philo(t_all *all);
int		check_die(long n, t_all *all);
void	*ft_check(void *data);
int		create_philo(t_all *all);
long	set_time(void);
void	ft_time(int num);
long	ft_atol(char *str);

#endif