/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:35:22 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/11 16:22:44 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// static int	ft_check_eat(t_philo *philo)
// {
// 	static int done;

// 	if (philo->eat_count == philo->data->nbr_philo_must_eat)
// 		done++;
// 	// printf("!! %d\n", done);
// 	if (done >= philo->data->nbr_of_philo)
// 	{
// 		// pthread_mutex_lock(&philo->data->mutex_print);
// 		return (0);
// 	}
// 	return (1);
// }

static void *monitor(void *data_tmp)
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
			// if (data->is_nbr_eat == true)
			// 	if (!ft_check_eat(&data->philos[i]))
			// 		return (0);
			if (data->end == true)
				return (0);
			if (get_time() -  data->philos[i].start_philo_life - data->philos[i].last_eat_time >
				data->live_time)
			{
				pthread_mutex_lock(&data->mutex_print);
				printf(R"%llu %d died\n"RS, get_time() - data->start_time, i + 1);
				return (0);
			}
			i++;
		}
	}
}

void *ft_monitor(void *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, (void *)data) == -1)
		error_return_void("failed to create monitor as thread");
	pthread_join(monitor_thread, NULL);
	return (NULL);
}
