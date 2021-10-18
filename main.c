/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:18 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/18 20:22:41 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks(t_philo *philos)
{
	pthread_mutex_lock(&(philos->data->forks[philos->l_fork]));
	print_message(philos->data, philos->id, FORK);
	pthread_mutex_lock(&(philos->data->forks[philos->r_fork]));
	print_message(philos->data, philos->id, FORK);
}

void ft_sleep(t_philo *philos)
{
	print_message(philos->data, philos->id, SLEEP);
	pthread_mutex_unlock(&(philos->data->forks[philos->l_fork]));
	pthread_mutex_unlock(&(philos->data->forks[philos->r_fork]));
	usleep(philos->data->time_to_sleep);
}

void eat(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->to_do);
	print_message(philos->data, philos->id, EAT);
	philos->eat_count++;
	usleep(philos->data->time_to_eat);
	pthread_mutex_unlock(&philos->data->to_do);
}

void *start(void *philos_tmp)
{
	t_philo *philos;
	philos = philos_tmp;

	while (1)
	{	
		if (philos->eat_count == philos->data->nbr_philo_must_eat)
			philos->done = 1;
		take_forks(philos);
		eat(philos);
		ft_sleep(philos);
		print_message(philos->data, philos->id, THINK);
	}
	print_message(philos->data, philos->id, EAT);
	return (NULL);
}

int philo_create(t_data *data)
{
	int				i;
	int				ret;
	pthread_t		philo[data->nbr_of_philo];

	i = 0;
	data->start_time = get_time();
	while (i < data->nbr_of_philo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, start, &(data->philos[i])) == -1)
		{
			write(2, "failed to create philo live as thread\n", 39);
			return (-1);
		}
		pthread_detach(data->philos[i].thread);
		i++;
		my_sleep(1000000);
	}
	return (0);
}


void *monitor(void *data_tmp)
{
	t_data	*data;
	int		i;
	int		done;

	data = (t_data *)data_tmp;
	while (1)
	{
		i = 0;
		done = 1;
		while (i < data->nbr_of_philo)
		{
			if (data->philos[i].done == 0)
				done = 0;
			i++;
		}
		if (done == 1)
		{
			pthread_mutex_lock(&data->mutex_print);
			return (NULL);
		}
	}
}

void *ft_monitor(void *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, (void *)data) == -1)
		return (NULL);
	pthread_join(monitor_thread, NULL);
	return (NULL);
}

int main(int argc, char **argv)
{
	t_data		data;
	int			i = 1;

	if (argc != 5 && argc != 6)
	{
		write (2, "invalid number of arg\n", 23);
		return (-1);
	}
	data.nbr_of_philo = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.nbr_philo_must_eat = 0;
	if (argc == 6)
		data.nbr_philo_must_eat = ft_atoi(argv[5]);
	init_philos(&data);
	init_mutex(&data);
	if (philo_create(&data) != 0)
		return (-1);
	if (argc == 6)
		ft_monitor(&data);
}
