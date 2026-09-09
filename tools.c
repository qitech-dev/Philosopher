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

void	set_dead_flag(t_data *data)//stop process
{
	pthread_mutex_lock(&data->dead_lock);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}

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

void	precise_sleep(long long duration, t_data *data)
{
	long long	start;

	start = get_time_ms();
	while (!check_dead_flag(data))//make sure other philos not die
	{
		if ((get_time_ms() - start) >= duration)
			break ;
		usleep(500);
	}
}

int	check_start_flag(t_data *data)
{
	int	flag;

	pthread_mutex_unlock(&data->dead_lock);
	flag = data->start_flag;
	pthread_mutex_unlock(&data->dead_lock);
	return (flag);
}

void	set_start_flag(t_data *data)//let all philos begin at same time
{
	pthread_mutex_lock(&data->dead_lock);
	data->start_flag = 1;
	pthread_mutex_unlock(&data->dead_lock);
}
