/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:29:27 by qijin             #+#    #+#             */
/*   Updated: 2026/04/04 16:29:28 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	t_data			*data;
};

struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	long long		start_time;
	int				start_flag;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				write_lock_ready;//whether was successfully initialized
	int				dead_lock_ready;//whether was successfully initialized
	int				forks_ready;//how many
	int				meal_locks_ready;//how many
};

int			parse_args(int argc, char **argv, t_data *data);
int			init_data(t_data *data);
int			init_philo(t_data *data);
void		cleanup_data(t_data *data);
int			check_dead_flag(t_data *data);
void		set_dead_flag(t_data *data);
long long	get_time_ms(void);
void		print_status(t_philo *philo, char *status);
void		precise_sleep(long long duration, t_data *data);
int			check_start_flag(t_data *data);
void		set_start_flag(t_data *data);
int			start_simulation(t_data *data);
int			take_forks(t_philo *philo);
int			eat(t_philo *philo);
void		release_forks(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		think(t_philo *philo);
void		print_death(t_philo *philo);
void		monitor_simulation(t_data *data);
void		precise_sleep_until(long long deadline, t_data *data);

#endif
