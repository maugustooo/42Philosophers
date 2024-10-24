/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:45 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/24 15:59:01 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_unlock_forks(t_philo *philo, int what_to_do, char *order)
{
	if (what_to_do == 1)
	{
		if (!ft_strcmp(order, "even"))
		{
			pthread_mutex_lock(philo->r_fork);
			pthread_mutex_lock(philo->l_fork);
		}
		else if (!ft_strcmp(order, "odd"))
		{
			pthread_mutex_lock(philo->l_fork);
			pthread_mutex_lock(philo->r_fork);
		}
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}

void	ft_sleep_and_think(t_philo *philo)
{
	if (died(philo))
		return ;
	printf("%ld philo %d is sleeping\n", ft_get_time() - philo->start_time,
		philo->id);
	if (ft_usleep(philo, philo->table->time_to_sleep))
		return ;
	printf("%ld philo %d is thinking\n", ft_get_time() - philo->start_time,
		philo->id);
}

void	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		lock_unlock_forks(philo, 1, "even");
	else
		lock_unlock_forks(philo, 1, "odd");
	if (died(philo))
		return (lock_unlock_forks(philo, 2, NULL));
	printf("%ld philo %d has taken a fork\n", ft_get_time() - philo->start_time,
		philo->id);
	if (died(philo))
		return (lock_unlock_forks(philo, 2, NULL));
	printf("%ld philo %d has taken a fork\n", ft_get_time() - philo->start_time,
		philo->id);
	philo->is_eating = 1;
	philo->last_meal = ft_get_time();
	philo->meals--;
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->meals == 0)
		philo->table->count++;
	pthread_mutex_unlock(&philo->table->mutex);
	printf("count: %d\n", philo->table->count);
	if (died(philo))
		return (lock_unlock_forks(philo, 2, NULL));
	printf("%ld philo %d is eating\n", ft_get_time() - philo->start_time,
		philo->id);
	if (ft_usleep(philo, philo->table->time_to_eat))
		return (lock_unlock_forks(philo, 2, NULL));
	philo->is_eating = 0;
	lock_unlock_forks(philo, 2, NULL);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->table->num_philos == 1)
	{
		printf("%ld philo %d has taken a fork\n", ft_get_time()
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
