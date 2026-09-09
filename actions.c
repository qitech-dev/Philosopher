/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <qijin@learner.42.tech>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:36:48 by qijin             #+#    #+#             */
/*   Updated: 2026/09/09 16:36:49 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	select_forks(t_philo *philo, pthread_mutex_t **first, pthread_mutex_t ** second)
{
	if (philo->id % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	select_forks(philo, first, second);
	pthread_mutex_lock(first);
	if (check_dead_flag(philo->data))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(second);
	if (check_dead_flag(philo->data))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (0);
	}
	print_status(philo, "has taken a fork");
	return (1);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, "is eating");
	precise_sleep(philo->data->time_to_eat, philo->data);
	if (!check_dead_flag(philo->data))
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meal_lock);
	}
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
