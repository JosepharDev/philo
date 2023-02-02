#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>


#define FORK "has taken a fork"
#define SLEEP "is sleeping"
#define EAT "is eating"
#define THINK "is thinking"
#define DIE "died"


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
	long			last_eat;
	t_num 			num;
	pthread_t 		philo;
	pthread_mutex_t *forks;
	pthread_mutex_t *next_fork;
	pthread_mutex_t mutex_print;
}t_philo;



typedef struct s_all
{
	t_philo 		*philo;
	t_num 			num;
	pthread_mutex_t *forks;
}t_all;



int ft_check_die(t_all *all);
void ft_time(int num);
void ft_init(t_all *all, char **av);
void init_philo(t_all *all, pthread_mutex_t mutex_print);
long long ft_atol(char *str);
void *func(void *p);
long set_time(void);
#endif