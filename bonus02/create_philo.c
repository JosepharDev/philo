#include "philo.h"

int create_philo(t_all *all)
{
	int	i;
	pthread_t thread;

	i = -1;
	while (++i < all->philo.num_of_philo)
	{
		all->index = i + 1;
		all->pid[i] = fork();
		if (all->pid[i] == -1)
		{
			while(i >= 0)
				kill(all->pid[i--], SIGKILL);
			printf("Error in fork\n");
			exit(-1);
		}
		else if(all->pid[i] == 0)
		{
			if (pthread_create(&thread, NULL, ft_check, all) != 0)
				{
					printf("Error in pthread_create");
					exit(-1);
				}
			if (pthread_detach(thread) != 0)
				{
					printf("Error in pthread_create");
					exit(-1);
				}
			life_philo(all);
			exit(0);
		}
	}
	return (0);
}