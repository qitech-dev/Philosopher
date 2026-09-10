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

static int	philo_has_died(t_philo *philo, long long cutoff)
{
	pthread_mutex_lock(&philo->meal_lock);
	if ((cutoff - philo->last_meal_time) >= philo->data->time_to_die)
	{
		print_death(philo);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static long long	get_quota_time(t_philo *philo)
{
	long long	finished;

	pthread_mutex_lock(&philo->meal_lock);
	finished = philo->quota_time;
	pthread_mutex_unlock(&philo->meal_lock);
	return (finished);
}

static long long	all_ate_enough(t_data *data)
{
	int			i;
	long long	finished;
	long long	latest;

	if (data->must_eat_times == -1)
		return (0);
	i = 0;
	latest = 0;
	while (i < data->num_of_philos)
	{
		finished = get_quota_time(&data->philos[i]);
		if (!finished)
			return (0);
		if (finished > latest)
			latest = finished;
		i++;
	}
	return (latest);
}

void	monitor_simulation(t_data *data)
{
	int			i;
	long long	cutoff;
	long long	finished;

	while (!check_dead_flag(data))
	{
		cutoff = get_time_ms();
		finished = all_ate_enough(data);
		if (finished)
			cutoff = finished;
		i = 0;
		while (i < data->num_of_philos)
		{
			if (philo_has_died(&data->philos[i], cutoff))
				return ;
			i++;
		}
		if (finished)
		{
			set_dead_flag(data);
			return ;
		}
		usleep(500);
	}
}
