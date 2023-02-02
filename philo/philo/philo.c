#include "philo.h"

int thread_create(t_all *all)
{
  int i;

  i = 0;
  while (i < all->num.num_philo)
  {
    if (pthread_create(&all->philo[i].philo, NULL, &func, &all->philo[i]) != 0)
      {
        printf("Error in pthread_create");
        return (-1);
      }
      i++;
  }
  if (ft_check_die(all) == 11)
    return (-1);
  return (0);
}

int main(int ac, char **av)
{
  t_all all;
  int i;

  i = 0;
  if (ac == 5 || ac == 6)
  {
    ft_init(&all, av);
    if (thread_create(&all) == -1)
      return (1);
  }
  else
    printf("Invalid Argemment\n");
  return (0);
}