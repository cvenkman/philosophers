/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:35:22 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/11 18:18:05 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*monitor(void *data_tmp)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_tmp;
	while (1)
	{
		i = 0;
		usleep(50);
		while (i < data->nbr_of_philo)
		{
			if (data->end == true)
				return (0);
			if (get_time() - data->philos[i].start_philo_life
				- data->philos[i].last_eat_time > data->live_time)
			{
				pthread_mutex_lock(&data->mutex_print);
				printf(R"%lu %d died\n"RS, get_time() - data->start_time, i + 1);
				return (0);
			}
			i++;
		}
	}
}

void	*ft_monitor(void *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, (void *)data) == -1)
		error_return_void("failed to create monitor as thread");
	pthread_join(monitor_thread, NULL);
	return (NULL);
}
