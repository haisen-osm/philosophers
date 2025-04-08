#include "philo.h"

void log_action(t_philo *philo, char *msg)
{
	long timestamp;

	timestamp = get_time_in_ms() - philo->sim->start_time;
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (!philo->sim->someone_died)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->sim->print_mutex);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (!philo->sim->someone_died)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		philo->last_meal_time = get_time_in_ms();
		log_action(philo, "eating");
		usleep(philo->config->time_to_eat * 1000);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		log_action(philo, "sleeping");
		usleep(philo->config->time_to_sleep * 1000);
		log_action(philo, "thinking");
	}

	return NULL;
}
// ! stop here for a break
void *simulation(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	t_sim *sim = philos[0].sim;
	int i;

	while (1)
	{
		if (sim->someone_died)
			break;
		i = 0;
		int full_philos = 0;
		while (i < sim->config->num_philos)
		{
			long now = get_time_in_ms();
			pthread_mutex_lock(&sim->death_mutex);
			if (now - philos[i].last_meal_time > sim->config->time_to_die)
			{
				log_action(&philos[i], "died");
				sim->someone_died = 1;
				pthread_mutex_unlock(&sim->death_mutex);
				return NULL;
			}
			if (sim->config->has_must_eat &&
				philos[i].meals_eaten >= sim->config->must_eat_count)
			{
				full_philos++;
			}
			pthread_mutex_unlock(&sim->death_mutex);
			i++;
		}
		if (sim->config->has_must_eat &&
			full_philos == sim->config->num_philos)
		{
			sim->someone_died = 1;
			break;
		}
		usleep(500);
	}

	return NULL;
}

void ft_dining(t_config *config, t_philo *philos, t_sim *sim)
{
	int i = 0;
	while (i < config->num_philos)
	{
		pthread_create(&philos[i].thread_id, NULL, philo_routine, (void *)&philos[i]);
		i++;
	}
	pthread_t simthr_id;
	pthread_create(&simthr_id, NULL, simulation, (void *)philos);
	i = 0;
	while (i < config->num_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}

	sim->someone_died = 0;
}
