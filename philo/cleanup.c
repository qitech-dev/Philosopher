/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 22:09:22 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 22:09:24 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
