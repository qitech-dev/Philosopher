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

static void	one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	precise_sleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->left_fork);
}

static int	run_one_cycle(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	if (!eat(philo))
	{
		release_forks(philo);
		return (0);
	}
	release_forks(philo);
	if (check_dead_flag(philo->data))
		return (0);
	philo_sleep(philo);
	if (check_dead_flag(philo->data))
		return (0);
	think(philo);
	return (1);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_start(philo->data);
	if (check_dead_flag(philo->data))
		return (NULL);
	if (philo->data->num_of_philos == 1)
	{
		one_philo_routine(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_sleep(philo->data->time_to_eat / 2, philo->data);
	while (!check_dead_flag(philo->data))
	{
		if (!run_one_cycle(philo))
			break ;
	}
	return (NULL);
}
