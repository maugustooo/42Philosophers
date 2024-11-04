/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:46:06 by maugusto          #+#    #+#             */
/*   Updated: 2024/11/04 14:35:02 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_unlock_forks(t_philo *philo, int what_to_do)
{
	if (philo->id % 2 == 0 && what_to_do == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(philo->r_fork);
	}
	else if (philo->id % 2 != 0 && what_to_do == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
	}
	if (philo->id % 2 == 0 && what_to_do != 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else if (philo->id % 2 != 0 && what_to_do != 1)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
}

void	log_event(t_philo *philo, const char *event)
{
	pthread_mutex_lock(&philo->table->mutex);
	if (philo->table->end)
	{
		pthread_mutex_unlock(&philo->table->mutex);
		return ;
	}
	printf("%ld %d %s\n", ft_get_time() - philo->start_time, philo->id, event);
	pthread_mutex_unlock(&philo->table->mutex);
}
