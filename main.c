#include "philo.h"

//! the input:
//! {number of philos} {time to die} {time to eat} {time to sleep}
//!         5             800           200           200

int ft_parsing(int ac, char **av, t_config *config)
{
	if (ac < 4)
	{
		printf("arguments missing\n");
		return -1;
	}
	config_init(config);
	if (check_args(av, config) == -1)
	{
		printf("checks failed\n");
		return -1;
	}
	return 0;
}

long get_time_in_ms()
{
	struct timeval test;
	gettimeofday(&test, NULL);
	long ms = test.tv_sec * 1000 + test.tv_usec / 1000;
	ms = test.tv_sec * 1000 + test.tv_usec / 1000;
	return (ms);
}

int main(int ac, char *av[])
{
	t_config config;
	if (ft_parsing(ac, av, &config) == -1)
		return EXIT_FAILURE;
	t_philo *philos = malloc(sizeof(t_philo) * config.num_philos);
	if (!philos)
		return 1;
	t_sim simulation;
	compl_init(philos, &simulation, &config);
	ft_dining(&config, philos, &simulation);

	return EXIT_SUCCESS;
}
