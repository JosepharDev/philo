/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoyahya <yoyahya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:15:41 by yoyahya           #+#    #+#             */
/*   Updated: 2023/02/09 20:00:54 by yoyahya          ###   ########.fr       */
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

# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_num
{
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		ntpe;
}t_num;

typedef struct s_philo
{
	int				index;
	int				num_of_eating;
	long			last_eat;
	long			start_time;
	t_num			num;
	pthread_t		philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*lock;
	struct s_all	*all;
}t_philo;

typedef struct s_all
{
	t_philo			*philo;
	t_num			num;
	pthread_mutex_t	*forks;
}t_all;

int			supervis(t_all *all);
void		ft_time(int num);
int			ft_init(t_all *all, char **av);
void		init_philo(t_all *all, pthread_mutex_t *mutex_print,
				pthread_mutex_t *lock);
long		ft_atol(char *str);
void		*func(void *p);
long		set_time(void);
void		ft_print(t_philo philo, char *str);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_take_fork(t_philo *philo);
#endif
