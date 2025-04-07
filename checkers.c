#include "philo.h"

int check_args(char **av, t_config *config)
{
	config->num_philos = ft_atoi(av[1]);
	config->time_to_die = ft_atoi(av[2]);
	config->time_to_eat = ft_atoi(av[3]);
	config->time_to_sleep = ft_atoi(av[4]);
	if (av[5] != NULL)
	{
		config->must_eat_count = ft_atoi(av[5]);
		config->has_must_eat = 1;
	}
	else
		config->has_must_eat = 0;
	if (config->num_philos == -1 || config->time_to_die == -1 || config->time_to_eat == -1 ||
		config->time_to_sleep == -1 || config->must_eat_count == -1)
		return -1;
	return 0;
}

int check_num(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return -1;
		i++;
	}
	return 0;
}