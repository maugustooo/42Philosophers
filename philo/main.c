/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:23:04 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/24 15:40:06 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_routine,
				(void *)&philo[i]) != 0)
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
		if (pthread_join(philo[i].thread, NULL) != 0)
		{
			printf("Error joining philo thread\n");
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_table			table;
	pthread_mutex_t	*forks;

	philo = NULL;
	memset(&table, 0, sizeof(t_table));
	if (!parse(argc, argv))
		return (0);
	init_table(&table, argv);
	forks = init_forks(table.num_philos);
	philo = init_philos(&table, forks);
	start_simulation(philo, &table);
	free(philo);
	free(forks);
}
