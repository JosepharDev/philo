#include "philo.h"

int init_philo(t_all *all)
{
	int	val;

	val = 0;
	all->start_time = set_time();
	all->num_of_eating = 0;
	val = sem_unlink("forks");
	val = sem_unlink("sem_print");
	val = sem_unlink("sem_lock");
	if (val == -1)
	{
		printf("Error in sem_unlink\n");
		exit(-1);
	}
	all->fork = sem_open("forks", O_CREAT, 0664, all->philo.num_of_philo);
	all->sem_lock = sem_open("sem_lock", O_CREAT, 0664, 1);
	all->sem_print = sem_open("sem_print", O_CREAT, 0664, 1);
	if (all->fork == SEM_FAILED || all->sem_lock == SEM_FAILED
		|| all->sem_print == SEM_FAILED)
	{
		printf("Error in sem_open\n");
		exit(-1);
	}
	return (0);
}

int init_struct(t_all *all, char **av)
{
	all->philo.num_of_philo = ft_atol(av[1]);
	all->philo.time_to_die = ft_atol(av[2]);
	all->philo.time_to_eat = ft_atol(av[3]);
	all->philo.time_to_sleep = ft_atol(av[4]);
	if (!av[5])
		all->philo.ntpe = -1;
	else
		all->philo.ntpe = ft_atol(av[5]);
	if (all->philo.num_of_philo <= 0 || all->philo.time_to_die <= 0
		|| all->philo.time_to_eat <= 0 || all->philo.time_to_sleep <= 0)
		{
			printf("invalid arg");
			return (-1);
		}
	all->fork = malloc(sizeof(sem_t) * all->philo.num_of_philo);
	all->sem_print = malloc(sizeof(sem_t));
	all->sem_lock = malloc(sizeof(sem_t));
	all->pid = malloc(sizeof(pid_t) * all->philo.num_of_philo);
	if (!all->fork || !all->sem_print || !all->sem_lock || !all->pid)
	{
		printf("Error in malloc");
		return (-1);
	}
	init_philo(all);
	return (0);
}

int main(int ac, char **av)
{
	t_all all;
	init_struct(&all, av);
	create_philo(&all);
	return (0);
}