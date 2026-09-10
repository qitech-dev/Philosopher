/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 02:07:49 by qijin             #+#    #+#             */
/*   Updated: 2026/09/10 02:07:50 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate_locked(t_data *data)
{
	int	i;

	if (data->must_eat_times <= 0)
		return (0);
	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat_times)
			return (0);
		i++;
	}
	return (1);
}

int	begin_meal(t_philo *philo, long long *meal_start)
{
	t_data		*data;
	int			started;

	data = philo->data;
	started = 0;
	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_lock(&data->dead_lock);
	*meal_start = get_time_ms();
	if (!data->dead_flag && !check_death_locked(data, *meal_start))
	{
		philo->last_meal_time = *meal_start;
		printf("%lld %d is eating\n",
			*meal_start - data->start_time, philo->id);
		started = 1;
	}
	pthread_mutex_unlock(&data->dead_lock);
	pthread_mutex_unlock(&data->write_lock);
	return (started);
}

int	finish_meal(t_philo *philo)
{
	t_data	*data;
	int		running;

	data = philo->data;
	pthread_mutex_lock(&data->write_lock);
	pthread_mutex_lock(&data->dead_lock);
	if (!data->dead_flag && !check_death_locked(data, get_time_ms()))
	{
		if (data->must_eat_times > 0
			&& philo->meals_eaten < data->must_eat_times)
			philo->meals_eaten++;
		if (all_ate_locked(data))
			data->dead_flag = 1;
	}
	running = !data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	pthread_mutex_unlock(&data->write_lock);
	return (running);
}
