#include "philo.h"

void config_init(t_config *config)
{
	config->num_philos = 0;
	config->time_to_die = 0;
	config->time_to_eat = 0;
	config->time_to_sleep = 0;
	config->must_eat_count = 0;
	config->has_must_eat = 0;
}
int compl_init(t_philo *philo, t_sim *sim, t_config *config)
{
	int i;

	i = 0;
	sim->config = config;
	sim->forks = malloc(sizeof(pthread_mutex_t) * config->num_philos);
	if (!sim->forks)
		return MALLOC_FAILED;
	sim->start_time = get_time_in_ms();
	while (i < config->num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return PTHREAD_MUTEX_FAILED;
		i++;
	}
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0 ||
		pthread_mutex_init(&sim->death_mutex, NULL) != 0 ||
		pthread_mutex_init(&sim->meal_mutex, NULL) != 0)
	{
		return PTHREAD_MUTEX_FAILED;
	}
	i = 0;
	while (i < config->num_philos)
	{
		philo[i].id = i + 1;
		philo[i].config = config;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = sim->start_time;
		philo[i].left_fork = &sim->forks[i];
		philo[i].right_fork = &sim->forks[(i + 1) % config->num_philos];
		philo[i].sim = sim;
		i++;
	}
	sim->philos = philo;
	sim->someone_died = 0;
	return 0;
}
