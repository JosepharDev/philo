#include "philo.h"
int main(int ac, char **av)
{
  t_all all;

  if (ac == 5 || ac == 6)
  {
    ft_init(&all, av);
  }
  else
    printf("Invalid Argemment\n");
  return (0);
}