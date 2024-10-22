/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:12:33 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/22 15:55:17 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_table(t_table *table, char **argv)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->max_meals = ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	pthread_mutex_init(&table->mutex, NULL);
}

pthread_mutex_t	*init_forks(int num_philo)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!forks)
		return (NULL);
	while (i < num_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_table *table, pthread_mutex_t *forks)
{
	int	i;
	t_philo *philo;
	
	i = 0;
	philo = malloc(sizeof(t_philo) * table->num_philos);
	if(!philo)
		return (0);
	while (i < table->num_philos)
	{
		philo[i].l_fork = &forks[i];
		if (i == table->num_philos - 1)
			philo[i].r_fork = &forks[0];
		else
			philo[i].r_fork = &forks[i + 1];
		philo[i].id = i;
		philo[i].meals = 0;
		philo[i].table = table;
		philo[i].last_meal = ft_get_time();
		i++;
	}
	return (philo);
}
