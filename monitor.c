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

static int	philo_has_died(t_philo *philo)
{
	long long	now;

	pthread_mutex_lock(&philo->meal_lock);
	now = get_time_ms();
	if ((now - philo->last_meal_time) >= philo->data->time_to_die)
	{
		print_death(philo);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static int	has_eaten_enough(t_philo *philo, int target)
{
	int	enough;

	pthread_mutex_lock(&philo->meal_lock);
	enough = (philo->meals_eaten >= target);
	pthread_mutex_unlock(&philo->meal_lock);
	return (enough);
}

static int	all_ate_enough(t_data *data)
{
	int	i;

	if (data->must_eat_times == -1)
		return (0);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (!has_eaten_enough(&data->philos[i], data->must_eat_times))
			return (0);
		i++;
	}
	return (1);
}

void	monitor_simulation(t_data *data)
{
	int			i;

	while (!check_dead_flag(data))
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (philo_has_died(&data->philos[i]))
				return ;
			i++;
		}
		if (all_ate_enough(data))
		{
			set_dead_flag(data);
			return ;
		}
		usleep(500);
	}
}
