/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:45 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/25 13:26:00 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_sleep_and_think(t_philo *philo)
{
	if (died(philo))
		return ;
	log_event(philo, "is sleeping");
	if (ft_usleep(philo, philo->table->time_to_sleep))
		return ;
	if (died(philo))
		return ;
	log_event(philo, "is thinking");
}

static int	check_and_release(t_philo *philo)
{
	if (died(philo))
	{
		lock_unlock_forks(philo, 2, NULL);
		return (1);
	}
	return (0);
}

static void	handle_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->mutex);
	philo->meals--;
	philo->last_meal = ft_get_time();
	if (philo->meals == 0)
		philo->table->count++;
	pthread_mutex_unlock(&philo->table->mutex);
}

static void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_unlock_forks(philo, 1, "even");
	else
		lock_unlock_forks(philo, 1, "odd");
	if (check_and_release(philo))
		return ;
	log_event(philo, "has taken a fork");
	if (check_and_release(philo))
		return ;
	log_event(philo, "has taken a fork");
	handle_meal(philo);
	if (check_and_release(philo))
		return ;
	log_event(philo, "is eating");
	if (ft_usleep(philo, philo->table->time_to_eat))
		return (lock_unlock_forks(philo, 2, NULL));
	lock_unlock_forks(philo, 2, NULL);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
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
	while (1)
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
		if (died(philo))
			break ;
	}
	return (pointer);
}
