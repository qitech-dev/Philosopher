/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 21:59:40 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 21:59:42 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_start_flag(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->dead_lock);
	flag = data->start_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (flag);
}

void	set_start_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	data->start_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

int	check_dead_flag(t_data *data)
{
	int	flag;

	pthread_mutex_lock(&data->dead_lock);
	flag = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (flag);
}

void	set_dead_flag(t_data *data)//stop process
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}
