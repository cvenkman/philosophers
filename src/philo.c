/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:18 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/14 03:11:13 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	take_forks(t_philo *philos)
{
	pthread_mutex_lock(&(philos->data->forks[philos->l_fork]));
	print_message(philos->data, philos->id, "\x1b[35m has taken a fork\x1b[0m");
	pthread_mutex_lock(&(philos->data->forks[philos->r_fork]));
	print_message(philos->data, philos->id, "\x1b[35m has taken a fork\x1b[0m");
}

static void	ft_sleep(t_philo *philo)
{
	print_message(philo->data, philo->id, "\x1b[32m is sleeping\x1b[0m");
	my_sleep(philo->data->time_to_sleep);
} 

static void	eat(t_philo *philo)
{
	philo->last_eat_time = get_time() - philo->start_philo_life;
	print_message(philo->data, philo->id, "\x1b[33m is eating\x1b[0m");
	my_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
	philo->eat_count++;
}

void	*start(void *philo_tmp)
{
	t_philo	*philo;

	philo = (t_philo *)philo_tmp;
	philo->start_philo_life = get_time();
	while (1)
	{
		if (philo->data->is_nbr_eat == true)
		{
			if (philo->eat_count == philo->data->nbr_philo_must_eat)
				philo->data->done++;
			if (philo->data->done == philo->data->nbr_of_philo)
				philo->data->end = true;
		}
		take_forks(philo);
		eat(philo);
		ft_sleep(philo);
		print_message(philo->data, philo->id, "\x1b[36m is thinking\x1b[0m");
	}
	return (NULL);
}
