/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:42:29 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/14 03:08:24 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	philo_create(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->nbr_of_philo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL,
				start, &(data->philos[i])) == -1)
			error_return("failed to create philo live as thread");
		i++;
		usleep(5);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_data		data;
	pthread_t	monitor_thread;

	i = 0;
	if (init_argv(argc, argv, &data)
		|| init_philos(&data) || init_mutex(&data))
		return (1);
	if (philo_create(&data) != 0)
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, (void *)&data) == -1)
		error_return("failed to create monitor as thread");
	pthread_join(monitor_thread, NULL);
	while (i < data.nbr_of_philo)
		pthread_detach(data.philos[i++].thread);
}
