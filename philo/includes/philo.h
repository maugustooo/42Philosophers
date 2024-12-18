/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:07:33 by maugusto          #+#    #+#             */
/*   Updated: 2024/11/04 10:46:02 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>

typedef struct s_philo
{
	int				id;
	int				is_eating;
	long			start_time;
	int				meals;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	suseconds_t		last_meal;
	pthread_t		thread;
	struct s_table	*table;
}				t_philo;

typedef struct s_table
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	int				count;
	bool			end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
}				t_table;

bool			parse(int argc, char **argv);

suseconds_t		ft_get_time(void);
int				ft_usleep(t_philo *philo, long time);
int				died(t_philo *philo);
int				ft_atoi(const char *str);
long			ft_atol(const char *str);
int				ft_strcmp(const char *s1, const char *s2);

void			init_table(t_table *table, char **argv);
pthread_mutex_t	*init_forks(int num_philo);
t_philo			*init_philos(t_table *table, pthread_mutex_t *forks);	
void			free_forks(pthread_mutex_t *forks, int num_philo);
void			monitor(t_philo	*philo);

void			*philo_routine(void *pointer);
void			lock_unlock_forks(t_philo *philo, int what_to_do);
void			log_event(t_philo *philo, const char *event);