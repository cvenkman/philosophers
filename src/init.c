/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:21:36 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/26 09:47:54 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void init_philos(t_data *data)
{
	int			i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philos)
		return ;
	while (i < data->nbr_of_philo) //ft_bzero
	{
		ft_bzero(&data->philos[i], sizeof(t_philo));
		data->philos[i].id = i + 1;
		data->philos[i].done = 0;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = i + 1;
		if (data->philos[i].r_fork > data->nbr_of_philo - 1)
			data->philos[i].r_fork = 0;
		data->philos[i].data = data;
		data->philos[i].limit_time = 0;
		data->philos[i].start_day = 0;
		data->philos[i].last_eat_time = 0;
		data->philos[i].eat_count = 0;
		// data->start_time
		i++;
	}
}

int init_mutex(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->check_dead, NULL);
	pthread_mutex_init(&data->to_do, NULL);
	pthread_mutex_init(&data->eat_check, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if (!data->forks)
		return (-1);
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}
