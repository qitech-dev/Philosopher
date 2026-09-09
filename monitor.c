/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 17:25:26 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 17:25:28 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	get_last_meal_time(t_philo *philo)
{
	long long	last_meal;

	pthread_mutex_lock(&philo->meal_lock);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	return (last_meal);
}

void	monitor_simulation(t_data *data)
{
	int			i;
	long long	last_meal;

	while (!check_dead_flag(data))
	{
		i = 0;
		while(i < data->num_of_philos)
		{
			last_meal = get_last_meal_time(&data->philos[i]);
			if ((get_time_ms() - last_meal) >= data->time_to_die)
			{
				print_death(&data->philos[i]);
				return ;
			}
			i++;
		}
		usleep(500);
	}
}
