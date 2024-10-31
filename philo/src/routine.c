/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:45 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/31 19:36:54 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_sleep_and_think(t_philo *philo)
{
	log_event(philo, "is sleeping");
	if (ft_usleep(philo, philo->table->time_to_sleep))
		return ;
	if (philo->id % 2)
	{
		log_event(philo, "is thinking");
		if (ft_usleep(philo, philo->table->time_to_eat))
			return ;
	}
    else
	{
		log_event(philo, "is thinking");
		if (ft_usleep(philo, (philo->table->time_to_die
                - (philo->table->time_to_eat + philo->table->time_to_sleep
                    + philo->id))))
			return ;
	}
}

static void	handle_meal(t_philo *philo)
{
	philo->last_meal = ft_get_time();
	philo->meals--;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->meals == 0)
		philo->table->count++;
	pthread_mutex_unlock(&philo->table->mutex);
}

static void	ft_eat(t_philo *philo)
{
	lock_unlock_forks(philo, 1);
	log_event(philo, "has taken a fork");
	log_event(philo, "has taken a fork");
	handle_meal(philo);
	log_event(philo, "is eating");
	if (ft_usleep(philo, philo->table->time_to_eat))
		return (lock_unlock_forks(philo, 2));
	lock_unlock_forks(philo, 2);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	pthread_mutex_lock(&philo->table->mutex);
	pthread_mutex_unlock(&philo->table->mutex);
	if (philo->table->num_philos == 1)
	{
		printf("%ld %d has taken a fork\n", ft_get_time()
			- philo->start_time, philo->id);
		ft_usleep(philo, philo->table->time_to_die);
		pthread_mutex_lock(&philo->table->mutex);
		philo->table->end = true;
		pthread_mutex_unlock(&philo->table->mutex);
		return (pointer);
	}
	while (!died(philo))
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	return (pointer);
}
