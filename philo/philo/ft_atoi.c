#include "philo.h"

int ft_isspace(char c)
{
	if(c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (0);
	return (1);
}

long long ft_atol(char *str)
{
	int i = 0;
	int nbr = 0;
	int sign = 1;
	while(str[i] && ft_isspace(str[i]) == 0)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = - 1;
		i++;
	}
	while(str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10;
		nbr = nbr + str[i] - '0';
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
	{
		printf("contain other characters\n");
		return (-1);
	}
	else
		return (sign * nbr);
}