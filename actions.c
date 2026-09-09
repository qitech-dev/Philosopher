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

static int	start_meal(t_philo *philo, long long *meal_start)
{
	pthread_mutex_lock(&philo->meal_lock);
	*meal_start = get_time_ms();
	if ((*meal_start - philo->last_meal_time) >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		print_death(philo);
		return (0);
	}
	philo->last_meal_time = *meal_start;
	pthread_mutex_unlock(&philo->meal_lock);
	return (1);
}

int	eat(t_philo *philo)
{
	long long	meal_start;

	if (!start_meal(philo, &meal_start))
		return (0);
	print_status(philo, "is eating");
	precise_sleep_until(meal_start + philo->data->time_to_eat, philo->data);
	if (check_dead_flag(philo->data))
		return (0);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	return (1);
}

void	philo_sleep(t_philo *philo)
{
	long long	sleep_end;

	sleep_end = get_time_ms() + philo->data->time_to_sleep;
	print_status(philo, "is sleeping");
	precise_sleep_until(sleep_end, philo->data);
}

void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->data->num_of_philos % 2 == 1)
		precise_sleep(philo->data->time_to_eat / 2,
			philo->data);
}
