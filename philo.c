#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	printf("philo is: %d\n", philo->id);
	while (!philo->sim->someone_died)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d is eating\n", philo->last_meal_time, philo->id);
		philo->meals_eaten += 1;
		usleep(philo->config->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);

		printf("alive\n");
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
	usleep(20000);
	sim->someone_died = 1;
	i = 0;
	while (i < config->num_philos)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}

	sim->someone_died = 0;
}
