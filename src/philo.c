/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:18 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/11 03:54:02 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void take_forks(t_philo *philos)
{
	pthread_mutex_lock(&(philos->data->forks[philos->l_fork]));
	print_message(philos->data, philos->id, FORK);
	pthread_mutex_lock(&(philos->data->forks[philos->r_fork]));
	print_message(philos->data, philos->id, FORK);
}

void ft_sleep(t_philo *philo)
{
	print_message(philo->data, philo->id, SLEEP);
	my_sleep(philo->data->time_to_sleep);
}

void eat(t_philo *philo)
{
	print_message(philo->data, philo->id, EAT);
	philo->last_eat_time = get_time() - philo->start_philo_life;
	my_sleep(philo->data->time_to_eat);
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
}

void *start(void *philo_tmp)
{
	t_philo *philo;
	philo = (t_philo *)philo_tmp;
	philo->start_philo_life = get_time();
	while (philo->data->stop != 1)
	{
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
		i++;
		my_sleep(1);
	}
	return (0);
}



int main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (init_argv(argc, argv, &data) ||
		init_philos(&data) || init_mutex(&data))
		return (1);
	if (philo_create(&data) != 0)
		return (1);
	ft_monitor(&data);
	i = 0;
	while (i < data.nbr_of_philo)
	{
		pthread_detach(data.philos[i].thread);
		i++;
	}
}
