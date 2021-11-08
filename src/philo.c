/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:18 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/08 18:36:57 by cvenkman         ###   ########.fr       */
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
	philo->live_time = get_time() - philo->data->start_time;
	print_message(philo->data, philo->id, SLEEP);
	my_sleep(philo->data->time_to_sleep);
	// printf("#########  %llu   %llu\n", philo->last_eat_time, get_time() - philo->data->start_time);
}

void eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->to_do);
	print_message(philo->data, philo->id, EAT);
	my_sleep(philo->data->time_to_eat);
	philo->eat_count++;
	philo->last_eat_time = get_time() - philo->data->start_time - philo->start_day;
	// printf("last_eat_time   %llu\n", philo->last_eat_time);
	pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
	// pthread_mutex_unlock(&philo->data->to_do);
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
	while (i < data->nbr_of_philo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, start, &(data->philos[i])) == -1)
			error_return("failed to create philo live as thread");
		i += 2;
		my_sleep(10);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data		data;
	int			i = 1;

	if (argc != 5 && argc != 6)
		return (error_return("invalid number of arg"));
	data.nbr_of_philo = ft_atoi(argv[1]);
	data.live_time = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.nbr_philo_must_eat = 0;
	data.start_time = 0;
	data.stop = 0;
	data.is_nbr_eat = false;
	if (argc == 6)
	{
		data.nbr_philo_must_eat = ft_atoi(argv[5]);
		data.is_nbr_eat = true;
	}
	init_philos(&data);
	init_mutex(&data);
	if (philo_create(&data) != 0)
		return (-1);
	ft_monitor(&data);
	i = 0;
	while (i < data.nbr_of_philo)
	{
		pthread_detach(data.philos[i].thread);
		i++;
	}
}
