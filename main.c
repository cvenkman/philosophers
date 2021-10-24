/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:18 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/24 03:30:28 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void take_forks(t_philo *philos)
{
	pthread_mutex_lock(&(philos->data->forks[philos->l_fork]));
	print_message(philos->data, philos->id, FORK);
	pthread_mutex_lock(&(philos->data->forks[philos->r_fork]));
	print_message(philos->data, philos->id, FORK);
	// printf("fork\n");
}

void ft_sleep(t_philo *philos)
{
	print_message(philos->data, philos->id, SLEEP);
	my_sleep(philos->data->time_to_sleep);
	// printf("sleep\n");
}

void eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->to_do);
	print_message(philo->data, philo->id, EAT);
	philo->last_eat_time = get_time() - philo->data->start_time;
	my_sleep(philo->data->time_to_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
	// printf("eat\n");
	// pthread_mutex_unlock(&philo->data->to_do);
}

void *start(void *philos_tmp)
{
	t_philo *philos;
	philos = (t_philo *)philos_tmp;

	while (philos->data->stop != 1)
	{	
		if (philos->eat_count == philos->data->nbr_philo_must_eat)
			philos->done = 1;
		take_forks(philos);
		eat(philos);
		// philos->eat_count++;
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

	i = 0;
	data->start_time = get_time();
	
	// printf("55  %llu\n", data->start_time);
	while (i < data->nbr_of_philo)
	{
		if (pthread_create(&(data->philos[i].thread), NULL, start, &(data->philos[i])) == -1)
			return_error("failed to create philo live as thread");
		if (pthread_create(&(data->philos[i].thread), NULL, monitor, &(data->philos[i])) == -1)
			return_error("failed to create monitor as thread");
		pthread_join(data->philos[i].monitor, NULL);
		pthread_detach(data->philos[i].thread);
		i++;
		my_sleep(10);
	}
	return (0);
}

void *monitor(void *philos_tmp)
{
	t_philo *philo;
	int		i;
	int		done;
	unsigned int start_time;
	pthread_mutex_t		to_do;

	philo = (t_philo *)philos_tmp;
	done = 0;
	// start_time = data->start_time;
	while (1)
	{
		pthread_mutex_lock(&to_do);
		if (philo->eat_count == philo->data->nbr_philo_must_eat)
			done++;
		// printf("-- %d\n", done);
			// if ((get_time() - start_time - data->philos[i].last_eat_time) >
			// 	data->philos[i].d)
			// {
			// 	printf("==== %llu %llu\n", (get_time() - data->start_time),
			// 		data->philos[i].d);
			// 	print_message(data, data->philos[i].id, DIE);
			// 	return (NULL);
			// }
		if (done >= philo->data->nbr_of_philo)
		{
			printf("done = %d %d\n", done, philo->id);
			pthread_mutex_lock(&philo->data->mutex_print);
			exit (0);
		}
		pthread_mutex_unlock(&to_do);
	}
}

// void *ft_monitor(void *data)
// {
// 	pthread_t	monitor_thread;

// 	if (pthread_create(&monitor_thread, NULL, monitor, (void *)data) == -1)
// 		return (NULL);
// 	pthread_join(monitor_thread, NULL);
// 	return (NULL);
// }

int main(int argc, char **argv)
{
	t_data		data;
	int			i = 1;

	if (argc != 5 && argc != 6)
		return (return_error("invalid number of arg"));
	data.nbr_of_philo = ft_atoi(argv[1]);
	data.live_time = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.nbr_philo_must_eat = 0;
	data.start_time = 0;
	data.stop = 0;
	if (argc == 6)
		data.nbr_philo_must_eat = ft_atoi(argv[5]);
	init_philos(&data);
	init_mutex(&data);
	if (philo_create(&data) != 0)
		return (-1);
	// if (argc == 6)
		// ft_monitor(&data);
}
