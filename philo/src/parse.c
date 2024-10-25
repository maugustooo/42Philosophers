/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maugusto <maugusto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:18:59 by maugusto          #+#    #+#             */
/*   Updated: 2024/10/25 15:57:49 by maugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

bool	check_errors(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atol(argv[i]) <= 0 || ft_atol(argv[i]) > INT_MAX
			|| ft_str_isdigit(argv[i]))
		{
			printf("Error: Invalid argument\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	parse(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (ft_atol(argv[1]) < 1)
		{
			printf("Error: Number of philosophers must be greater than 0\n");
			return (false);
		}
		if (!check_errors(argc, argv))
			return (false);
		return (true);
	}
	else
	{
		printf("Error: arguments must be: number_of_philosophers, time_to_die, "
			"time_to_eat, time_to_sleep, "
			"opcional:number_of_times_each_philosopher_must_eat\n");
		return (false);
	}
}
