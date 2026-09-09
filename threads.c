/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:06:52 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 16:06:53 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_data *data)
{
	while (!check_start_flag(data))
		usleep(100);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start(philo->data);
	if (!check_dead_flag(philo->data))
		return (NULL);
	if (!take_forks(philo))
		return (NULL);
	eat(philo);
	release_forks(philo);
	if (check_dead_flag(philo->data))
		return (NULL);
	philo_sleep(philo);
	if (check_dead_flag(philo->data))
		return (NULL);
	think(philo);
	return (NULL);
}

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

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]) != 0)
		{
			printf("Error: Thread creation failed.\n");
			set_dead_flag(data);
			set_start_flag(data);//release the preceding process.
			join_threads(data, i);
			return (1);
		}
		i++;
	}
	data->start_time = get_time_ms();
	i = 0;
	while (i <data->num_of_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
	set_start_flag(data);
	join_threads(data, data->num_of_philos);
	return (0);
}
