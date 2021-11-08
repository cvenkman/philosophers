/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:18 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/08 23:40:16 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void take_forks(t_philo *philos)
{
	pthread_mutex_lock(&(philos->data->forks[philos->l_fork]));
	print_message(philos->data, philos->id, FORK);
	pthread_mutex_lock(&(philos->data->forks[philos->r_fork]));
	print_message(philos->data, philos->id, FORK);
	// printf("dws\n");
}

void ft_sleep(t_philo *philo)
{
	// philo->live_time = get_time() - philo->data->start_time;
	print_message(philo->data, philo->id, SLEEP);
	my_sleep(philo->data->time_to_sleep);
	// philo->last_eat_time = get_time() - philo->data->start_time - philo->start_day;
	// printf("last_eat_time   %llu\n", philo->last_eat_time);
	// printf("#########  %llu   %llu\n", philo->last_eat_time, get_time() - philo->data->start_time);
}

void eat(t_philo *philo)
{
	print_message(philo->data, philo->id, EAT);
	my_sleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->to_do);
	philo->last_eat_time = get_time() - philo->data->start_time - philo->start_day;
	printf("last_eat_time   %llu\n", philo->last_eat_time);
	pthread_mutex_unlock(&philo->data->to_do);
	// philo->last_eat_time = get_time() - philo->data->start_time - philo->start_day;
	// printf("last_eat_time   %llu\n", philo->last_eat_time);
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
}

void *start(void *philo_tmp)
{
	t_philo *philo;
	philo = (t_philo *)philo_tmp;
	while (philo->data->stop != 1)
	{
		philo->start_day = get_time() - philo->data->start_time;
		if (philo->eat_count == philo->data->nbr_philo_must_eat)
			philo->done = 1;
		take_forks(philo);
		eat(philo);
		ft_sleep(philo);
		print_message(philo->data, philo->id, THINK);
	}
	print_message(philo->data, philo->id, EAT);
	return (NULL);
}

int philo_create(t_data *data)
{
	int				i;
	int				ret;

	i = 0;
	data->start_time = get_time();
	while (i < data->nbr_of_philo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, start, &(data->philos[i])) == -1)
			error_return("failed to create philo live as thread");
		i += 2;
		my_sleep(10);
	}
	i = 1;
	my_sleep(10);
	while (i < data->nbr_of_philo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, start, &(data->philos[i])) == -1)
			error_return("failed to create philo live as thread");
		i += 2;
		my_sleep(10);
	}
	return (0);
}

int init_argv(int argc, char **argv, t_data *data)
{
	char **valid_arg;
	char **if_one_arg;
	if (argc == 2)
	{
		if_one_arg = ft_split(argv[1], ' ');
		if (arr_len(if_one_arg) != 5 && arr_len(if_one_arg) != 6)
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

int main(int argc, char **argv)
{
	t_data		data;
	int			i = 0;


	if (init_argv(argc, argv, &data) ||
		init_philos(&data) || init_mutex(&data))
		return (error_return("malloc error"));
	if (philo_create(&data) != 0)
		return (1);
	i = 0;
	while (i < data.nbr_of_philo)
	{
		pthread_detach(data.philos[i].thread);
		i++;
	}
	ft_monitor(&data);
}
