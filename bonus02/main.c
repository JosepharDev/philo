#include "philo.h"

int	init_philo(t_all *all)
{
	all->start_time = set_time();
	all->num_of_eating = 0;
	sem_unlink("/forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_lock");
	all->fork = sem_open("/forks", O_CREAT, 0664, all->philo.num_of_philo);
	all->sem_lock = sem_open("/sem_lock", O_CREAT, 0664, 1);
	all->sem_print = sem_open("/sem_print", O_CREAT, 0664, 1);
	if (all->fork == SEM_FAILED || all->sem_lock == SEM_FAILED
		|| all->sem_print == SEM_FAILED)
	{
		printf("Error in sem_open\n");
		exit(-1);
	}
	return (0);
}

int	init_struct(t_all *all, char **av)
{
	all->philo.num_of_philo = ft_atol(av[1]);
	all->philo.time_to_die = ft_atol(av[2]);
	all->philo.time_to_eat = ft_atol(av[3]);
	all->philo.time_to_sleep = ft_atol(av[4]);
	if (!av[5])
		all->philo.ntpe = -1;
	else
	{
		all->philo.ntpe = ft_atol(av[5]);
		if (all->philo.num_of_philo <= 0 || all->philo.time_to_die <= 0
			|| all->philo.time_to_eat <= 0 || all->philo.time_to_sleep <= 0
				|| all->philo.ntpe <= 0)
			{
				printf("invalid arg");
				return (-1);
			}
	}
	all->pid = malloc(sizeof(pid_t) * all->philo.num_of_philo);
	if (!all->pid)
	{
		printf("Error in malloc");
		return (-1);
	}
	init_philo(all);
	return (0);
}

int	ft_kill(t_all *all)
{
	int	i;

	i = -1;
	while(++i < all->philo.num_of_philo)
		kill(all->pid[i], SIGKILL);
	return (0);
}

int	main(int ac, char **av)
{
	t_all all;
	int	val;
	if (ac == 5 || ac == 6)
	{
		init_struct(&all, av);
		create_philo(&all);
		waitpid(-1, &val, 0);
		if (val != 0)
			ft_kill(&all);
	}
	else
		printf("invalid arg\n");
	return (0);
}