/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:45 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/22 15:52:26 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philo_is_dead(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(&table->mutex);
	if (philo->end == true)
	{
		pthread_mutex_unlock(&table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->mutex);
	return (0);
}
void ft_sleep_and_think(t_philo *philo)
{
	printf("%d is sleeping\n", philo->id);
	usleep(philo->table->time_to_sleep);
	printf("%d is thinking\n", philo->id);
}

void ft_eat(t_philo *philo)
{
	if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	printf("%d has taken a fork\n", philo->id);
	printf("%d has taken a fork\n", philo->id);
	philo->is_eating = 1;
	philo->last_meal = ft_get_time();
	philo->meals--;
	printf("%d is eating\n", philo->id);
	usleep(philo->table->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void *philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
		if (philo_is_dead(philo, philo->table))
			break ;
	}
	return (pointer);
}