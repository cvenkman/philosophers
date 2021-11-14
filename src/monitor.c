/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:35:22 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/14 03:14:14 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitor(void *data_tmp)
{
	t_data	*data;
	int		i;
	char	msg_complete[50];
	int		msg_len;

	data = (t_data *)data_tmp;
	while (1)
	{
		i = 0;
		usleep(300);
		while (i < data->nbr_of_philo)
		{
			if (data->end == true)
				return (0);
			if (get_time() - data->philos[i].start_philo_life
				- data->philos[i].last_eat_time > data->live_time)
			{
				pthread_mutex_lock(&data->mutex_print);
				msg_len = get_msg_complete(&msg_complete, data, i + 1, "\x1b[31m died\x1b[0m");
				write(1, msg_complete, msg_len);
				return (0);
			}
			i++;
		}
	}
}
