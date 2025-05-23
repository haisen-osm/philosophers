#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>

#define MALLOC_FAILED 1
#define PTHREAD_CREATE_FAILED 2
#define PTHREAD_JOIN_FAILED 3
#define PTHREAD_MUTEX_FAILED 4

struct s_sim;
typedef struct s_sim t_sim;

typedef struct s_config
{
	int num_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int must_eat_count;
	int has_must_eat;
} t_config;

typedef struct s_philo
{
	int id;
	int meals_eaten;
	long last_meal_time;
	pthread_t thread_id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	t_config *config;
	t_sim *sim;
} t_philo;

typedef struct s_sim
{
	t_config *config;
	t_philo *philos;
	pthread_mutex_t *forks;
	long start_time;
	pthread_mutex_t print_mutex;
	int someone_died;
	pthread_mutex_t death_mutex;
	pthread_mutex_t meal_mutex;
} t_sim;

int ft_parsing(int ac, char **av, t_config *config);
int check_args(char **av, t_config *config);
int ft_atoi(char *str);
int check_num(char *str);
void config_init(t_config *config);
int compl_init(t_philo *philo, t_sim *sim, t_config *config);
int ft_dining(t_config *config, t_philo *philos);
void log_action(t_philo *philo, char *msg);
long get_time_in_ms();
void ft_putstr(char *str, int fd);
void print_err(char *err_msg);
int handle_error(int code);
void free_all(t_sim *sim, t_philo *philos);

#endif