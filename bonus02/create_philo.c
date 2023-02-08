#include "philo.h"

int create_philo(t_all *all)
{
	int	i;
	pid_t id;
	pthread_t thread;
	pid_t die;
	int val;

	i = 0;
	while (i < all->philo.num_of_philo)
	{
		all->index = i + 1;
		id = fork();
		if (id == -1)
		{
			printf("Error in fork\n");
			exit(-1);
		}
		else if(id == 0)
		{
			all->last_eat = set_time();
			pthread_create(&thread, NULL, ft_check, all);
			pthread_detach(thread);
			life_philo(all);
			exit(0);
		}
		else
			all->pid[i] = id;
		i++;
	}
	die = waitpid((pid_t)-1, &val, 0);
	if (val != 0)
	{
		i = 0;
		while(i < all->philo.num_of_philo)
		{
			if (all->pid[i] != die)
			{
				if (kill(all->pid[i], SIGKILL) != 0)
					printf("saasfaf");
			}
			i++;
		}
	}
	return (0);
}