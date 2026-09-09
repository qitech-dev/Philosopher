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

static int	join_threads(t_data *data, int thread_count)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < thread_count)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Error: Thread join failed.\n");
			set_dead_flag(data);
			status = 2;
		}
		i++;
	}
	return (status);
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
			if (join_threads(data, i) != 0)
				return (2);
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
	int	status;

	status = create_threads(data);
	if (status != 0)
		return (status);
	prepare_start(data);
	monitor_simulation(data);
	return (join_threads(data, data->num_of_philos));
}
