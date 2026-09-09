/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 22:00:22 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 22:00:23 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	if (!check_dead_flag(philo->data))
	{
		timestamp = get_time_ms() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}

void	print_death(t_philo *philo)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->write_lock);
	if (!check_dead_flag(philo->data))
	{
		set_dead_flag(philo->data);
		timestamp = get_time_ms() - philo->data->start_time;
		printf("%lld %d died\n", timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}
