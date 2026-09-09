/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 22:03:38 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 22:03:40 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_threads(t_data *data, int thread_count)
{
	int	i;

	i = 0;
	while (i < thread_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
		{
			printf("Error: Thread creation failed.\n");
			set_dead_flag(data);
			set_start_flag(data);
			join_threads(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	prepare_start(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	set_start_flag(data);
}

int	start_simulation(t_data *data)
{
	if (create_threads(data))
		return (1);
	prepare_start(data);
	monitor_simulation(data);
	join_threads(data, data->num_of_philos);
	return (0);
}
