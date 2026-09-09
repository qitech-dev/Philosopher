/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qijin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 15:23:18 by qijin             #+#    #+#             */
/*   Updated: 2026/04/12 15:23:20 by qijin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		status;

	if (parse_args(argc, argv, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
	{
		cleanup_data(&data);
		return (1);
	}
	if (init_philo(&data) != 0)
	{
		cleanup_data(&data);
		return (1);
	}
	status = start_simulation(&data);
	if (status == 2)
		return (1);
	cleanup_data(&data);
	return (0);
}
