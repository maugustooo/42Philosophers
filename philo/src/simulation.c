/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:35:09 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/22 15:40:47 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_meals(t_philo *philo, t_table *table)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->mutex);
		if(philo[i].meals == 0)
			count++;
		pthread_mutex_unlock(&table->mutex);
		i ++;
	}
	if(count == table->num_philos)
	{
		pthread_mutex_lock(&table->mutex);
		printf("Every philo ate their respective meals!\n");
		philo[i].end = true;
		pthread_mutex_unlock(&table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->mutex);
	return (0);
}
int philo_starve(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (ft_get_time() - philo->last_meal >= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int check_deaths(t_philo *philo, t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->mutex);
		if (philo_starve(&philo[i]) == 1)
		{
			pthread_mutex_unlock(&table->mutex);
			printf("%d died\n", philo[i].id);
			return (1);
		}
		pthread_mutex_unlock(&table->mutex);
		i++;
	}
	return (0);
}

void *monitor(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		if (check_deaths(philo, philo->table) == 1 || check_meals(philo, philo->table) == 1)
		{
			break ;
		}
	}
	return (pointer);
}

void start_simulation(t_philo **philo, t_table *table)
{
	pthread_t status;
	int i;

	i = 0;
	if(pthread_create(&status, NULL, &monitor, *philo) != 0)
	{
		printf("Error creating monitoring thread\n");
		return ;
	}
	while (i < table->num_philos)
	{
		if(pthread_create(&philo[i]->thread, NULL, &philo_routine, philo[i]) != 0)
		{
			printf("Error creating philo thread\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		if(pthread_join(philo[i]->thread, NULL) != 0)
		{
			printf("Error joining philo thread\n");
			return ;
		}
		i++;
	}
}
