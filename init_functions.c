/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fuctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:14:28 by qijin             #+#    #+#             */
/*   Updated: 2026/04/13 19:14:29 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_resource_state(t_data *data)
{
	data->forks = NULL;
	data->philos = NULL;
	data->write_lock_ready = 0;
	data->dead_lock_ready = 0;
	data->forks_ready = 0;
	data->meal_locks_ready = 0;
}

int	init_data(t_data *data)
{
	int	i;

	init_resource_state(data);
	data->start_time = 0;
	data->start_flag = 0;
	data->dead_flag = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
	{
		printf("Error: Memory allocation failed.\n");
		return (1);
	}
	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
	{
		printf("Error: Memory allocation failed.\n");
		return (1);
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		printf("Error: Mutex initialization failed.\n");
		return (1);
	}
	data->write_lock_ready = 1;
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		printf("Error: Mutex initialization failed.\n");
		return (1);
	}
	data->dead_lock_ready = 1;
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Error: Mutex initialization failed.\n");
			return (1);
		}
		data->forks_ready++;
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_of_philos];
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
		{
			printf("Error: Mutex initialization failed.\n");
			return (1);
		}
		data->meal_locks_ready++;
		i++;
	}
	return (0);
}

void	cleanup_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->meal_locks_ready)
	{
		pthread_mutex_destroy(&data->philos[i].meal_lock);
		i++;
	}
	i = 0;
	while (i < data->forks_ready)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	if (data->write_lock_ready)
		pthread_mutex_destroy(&data->write_lock);
	if (data->dead_lock_ready)
		pthread_mutex_destroy(&data->dead_lock);
	free(data->philos);
	free(data->forks);
	data->philos = NULL;
	data->forks = NULL;
}
