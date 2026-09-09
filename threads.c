/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:06:52 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 16:06:53 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_start(t_data *data)
{
	while (!check_start_flag(data))
		usleep(100);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start(s_data);
	if (!check_dead_flag(philo->data))
		print_status(philo, "is thinking");
	return (NULL);
}

static void	join_threads(t_data *data, int thread_count)
{
	int	i;

	i = 0;
	while (i < thread_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}
