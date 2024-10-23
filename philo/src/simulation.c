/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:35:09 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/23 13:32:32 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_simulation(t_philo *philo, t_table *table)
{
	int i;
	
	i = 0;
	while (i < table->num_philos)
	{
		if(pthread_create(&philo[i].thread, NULL, &philo_routine, (void *)&philo[i]) != 0)
		{
			printf("Error creating philo thread\n");
			return ;
		}
		i++;
	}
	monitor(philo);
	i = 0;
	while (i < table->num_philos)
	{
		if(pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("Error joining philo thread\n");
			return ;
		}
		i++;
	}
}
