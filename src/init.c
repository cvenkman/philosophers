/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:21:36 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/08 20:35:58 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init_philos(t_data *data)
{
	int			i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philos)
		return (1);
	while (i < data->nbr_of_philo)
	{
		ft_bzero(&data->philos[i], sizeof(t_philo));
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = i + 1;
		if (data->philos[i].r_fork > data->nbr_of_philo - 1)
			data->philos[i].r_fork = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
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
		return (1);
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_valid_argv(char **argv, t_data *data)
{
	data->nbr_of_philo = ft_atoi(argv[0]);
	data->live_time = ft_atoi(argv[1]);
	data->time_to_eat = ft_atoi(argv[2]);
	data->time_to_sleep = ft_atoi(argv[3]);
	data->nbr_philo_must_eat = 0;
	data->start_time = 0;
	data->stop = 0;
	data->is_nbr_eat = false;
	if (arr_len(argv) == 5)
	{
		data->nbr_philo_must_eat = ft_atoi(argv[5]);
		data->is_nbr_eat = true;
	}
	return (0);
}