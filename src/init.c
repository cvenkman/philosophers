/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:21:36 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/11 16:11:49 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

char	**validation(char **argv, int i)
{
	int		j;
	int		len;
	char	**new_arg;

	j = 0;
	new_arg = malloc(sizeof(char *) * (arr_len(argv)));
	while (argv[i])
	{
		new_arg[j] = ft_strtrim(argv[i], " 	");
		if (!new_arg[j])
			return (NULL);
		len = 0;
		if (new_arg[j][len] == '+' && ft_isdigit(new_arg[j][len + 1]))
			len++;
		while (new_arg[j][len])
		{
			if (!ft_isdigit(new_arg[j][len]))
				return (NULL);
			len++;
		}
		i++;
		j++;
	}
	new_arg[j] = NULL;
	return (new_arg);
}

int	init_argv(int argc, char **argv, t_data *data)
{
	char	**valid_arg;
	char	**if_one_arg;

	if (argc == 2)
	{
		if_one_arg = ft_split(argv[1], ' ');
		if (arr_len(if_one_arg) != 4 && arr_len(if_one_arg) != 5)
			return (error_return("invalid number of arguments"));
		valid_arg = validation(if_one_arg, 0);
		free_arr(if_one_arg);
	}
	else
	{
		if (argc != 5 && argc != 6)
			return (error_return("invalid number of arguments"));
		valid_arg = validation(argv, 1);
	}
	if (!valid_arg)
		return (error_return("invalid arguments"));
	init_valid_argv(valid_arg, data);
	free_arr(valid_arg);
	return (0);
}

int init_philos(t_data *data)
{
	int			i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philos)
		return (error_return("malloc error"));
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
		return (error_return("malloc error"));
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
	data->is_nbr_eat = false;
	data->done = 0;
	data->end = false;
	if (arr_len(argv) == 5)
	{
		data->nbr_philo_must_eat = ft_atoi(argv[4]);
		data->is_nbr_eat = true;
	}
	return (0);
}