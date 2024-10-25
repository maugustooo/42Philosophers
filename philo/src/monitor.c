/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:32:13 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/25 10:56:25 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_philo *philo, t_table *table)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	pthread_mutex_lock(&table->mutex);
	if (table->count == table->num_philos)
	{
		printf("Every philo ate their respective meals!\n");
		philo->table->end = true;
		pthread_mutex_unlock(&table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->mutex);
	return (0);
}

int	philo_starve(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (ft_get_time() - philo[i].last_meal >= philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}

int	check_deaths(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (philo_starve(philo, i) == 1)
		{
			pthread_mutex_lock(&table->mutex);
			philo->table->end = true;
			printf("%ld %d died\n", ft_get_time() - philo->start_time,
				philo[i].id);
			pthread_mutex_unlock(&table->mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

void	monitor(t_philo	*philo)
{
	while (1)
	{
		if (check_deaths(philo, philo->table) == 1
			|| check_meals(philo, philo->table) == 1)
			break ;
	}
}

int	died(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->end)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->mutex);
	return (0);
}
