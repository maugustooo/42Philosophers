/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:26:45 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/23 15:45:24 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void lock_unlock_forks(t_philo *philo, int what_to_do)
{
	if (what_to_do == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}
void ft_sleep_and_think(t_philo *philo)
{
	if(died(philo))
		return ;
	printf("%ld philo %d is sleeping\n",ft_get_time()- philo->start_time, philo->id);
	if(ft_usleep(philo, philo->table->time_to_sleep))
		return ;
	printf("%ld philo %d is thinking\n",ft_get_time()- philo->start_time, philo->id);
}

void ft_eat(t_philo *philo)
{
	if(philo->id % 2 == 0)
		lock_unlock_forks(philo, 1);
	else
		lock_unlock_forks(philo, 1);
	if (died(philo))
		return (lock_unlock_forks(philo, 2)) ;
	printf("%ld philo %d has taken a fork\n",ft_get_time()- philo->start_time,
		philo->id);
	if (died(philo))
		return (lock_unlock_forks(philo, 2)) ;
	printf("%ld philo %d has taken a fork\n", ft_get_time() - philo->start_time,
		philo->id);
	philo->is_eating = 1;
	philo->last_meal = ft_get_time();
	philo->meals--;
	if (died(philo))
		return (lock_unlock_forks(philo, 2));
	printf("%ld philo %d is eating\n",ft_get_time()- philo->start_time, philo->id);
	if(ft_usleep(philo, philo->table->time_to_eat))
		return (lock_unlock_forks(philo, 2));
    philo->is_eating = 0;
	lock_unlock_forks(philo, 2);
}

void *philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		ft_eat(philo);
		ft_sleep_and_think(philo);
		if (died(philo))
			break ;
	}
	return (pointer);
}
