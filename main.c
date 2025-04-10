#include "philo.h"

int ft_parsing(int ac, char **av, t_config *config)
{
	if (ac < 4)
	{
		print_err("Error: insufficient arguments.\n");
		return -1;
	}
	config_init(config);
	if (check_args(av, config) == 1)
	{
		printf("Error: invalid arguments (non-numeric or out of range)\n");
		return -1;
	}
	return 0;
}

long get_time_in_ms()
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (ms);
}

static int init_and_start_simulation(char **av, t_config *config)
{
	int status;
	t_philo *philos;
	t_sim simulation;

	if (ft_parsing(6, av, config) != 0)
		return EXIT_FAILURE;
	if (config->num_philos == 1)
	{
		usleep(config->time_to_die * 1000);
		printf("%d %d died", config->time_to_die, 1);
		return EXIT_SUCCESS;
	}
	philos = malloc(sizeof(t_philo) * config->num_philos);
	if (!philos)
		return handle_error(MALLOC_FAILED);
	status = compl_init(philos, &simulation, config);
	if (status != 0)
		return handle_error(status);
	status = ft_dining(config, philos);
	if (status != 0)
		return handle_error(status);
	free_all(&simulation, philos);
	return EXIT_SUCCESS;
}

int main(int ac, char **av)
{
	t_config config;

	if (ac < 5)
	{
		print_err("Error: insufficient arguments.\n");
		return EXIT_FAILURE;
	}
	return init_and_start_simulation(av, &config);
}
