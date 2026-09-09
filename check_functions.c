/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fuctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 18:22:22 by qijin             #+#    #+#             */
/*   Updated: 2026/04/12 18:22:23 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long int	ft_atol(const char *str)
{
	long	result;
	int		i;
	int		digit;

	result = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (result > ((INT_MAX - digit) / 10))
			return (-1);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments.\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("Error: Arguments must be numeric.\n");
			return (1);
		}
		i++;
	}
	data->num_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->num_of_philos <= 0 || data->time_to_die <= 0 ||
		data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf ("Error: Invalid argument values.\n");
		return (1);
	}
	if (argc == 6)
	{
		data->must_eat_times = ft_atol(argv[5]);
		if (data->must_eat_times <= 0)
		{
			printf("Error: Eat times must be positive.\n");
			return (1);
		}
	}
	else
		data->must_eat_times = -1;
	return (0);
}
