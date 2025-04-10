#include "philo.h"

void print_err(char *err_msg)
{
	ft_putstr(err_msg, 2);
}

int handle_error(int code)
{
	if (code == MALLOC_FAILED)
		print_err("Error: memory allocation failed.\n");
	else if (code == PTHREAD_CREATE_FAILED)
		print_err("Error: failed to create thread.\n");
	else if (code == PTHREAD_JOIN_FAILED)
		print_err("Error: failed to join thread.\n");
	else if (code == PTHREAD_MUTEX_FAILED)
		print_err("Error: mutex initialization failed.\n");
	else
		print_err("Error: unknown failure.\n");
	return EXIT_FAILURE;
}

void free_all(t_sim *sim, t_philo *philos)
{
	int i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->config->num_philos)
			pthread_mutex_destroy(&sim->forks[i++]);
		free(sim->forks);
	}
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->death_mutex);
	pthread_mutex_destroy(&sim->meal_mutex);
	if (philos)
		free(philos);
}
