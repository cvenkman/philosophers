/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:42:29 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/11 18:19:03 by cvenkman         ###   ########.fr       */
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
		i += 2;
		my_sleep(1);
	}
	i = 1;
	while (i < data->nbr_of_philo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL,
				start, &(data->philos[i])) == -1)
			error_return("failed to create philo live as thread");
		i += 2;
		my_sleep(1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (init_argv(argc, argv, &data)
		|| init_philos(&data) || init_mutex(&data))
		return (1);
	if (philo_create(&data) != 0)
		return (1);
	ft_monitor(&data);
	i = 0;
	while (i < data.nbr_of_philo)
		pthread_detach(data.philos[i++].thread);
}
