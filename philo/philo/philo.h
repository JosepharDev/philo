#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_num
{
	int num_philo;
	int time_to_die;
	int time_to_eat;
	int	time_to_sleep;
	int ntpe;
}t_num;

typedef struct s_philo
{
	int 			index;
	int 			num_of_eating;
	t_num 			num;
	pthread_t 		philo;
	pthread_mutex_t *forks;
	pthread_mutex_t *next_fork;
	pthread_mutex_t *mutex_print;
}t_philo;

typedef struct s_all
{
	t_philo 		*philo;
	t_num 			num;
	pthread_mutex_t *forks;
}t_all;


void ft_init(t_all *all, char **av);
void init_philo(t_all *all, pthread_mutex_t *mutex_print);
long long ft_atol(char *str);
#endif
