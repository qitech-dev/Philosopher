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
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time_ms();
	while (!check_dead_flag(data))
	{
		if ((get_time_ms() - start) >= duration)
			break ;
		usleep(500);
	}
}

void	precise_sleep_until(long long deadline, t_data *data)
{
	while (!check_dead_flag(data))
	{
		if (get_time_ms() >= deadline)
			break ;
		usleep(500);
	}
}
