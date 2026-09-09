/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 20:07:33 by qijin             #+#    #+#             */
/*   Updated: 2026/04/17 20:07:35 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec *1000) + (tv.tv_usec / 1000));
}

int	check_dead_flag(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->dead_lock);
	flag = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (flag);
}

void	set_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

void    *philo_routine(void *arg)
{
   (void)arg;
	return (NULL);
}
