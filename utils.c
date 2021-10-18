/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:12 by cvenkman          #+#    #+#             */
/*   Updated: 2021/10/18 18:23:12 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	// printf("time %lu\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void my_sleep(long int time)
{
	long int start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(1);
}

void print_message(t_data *data, int id, int msg)
{
	pthread_mutex_lock(&data->mutex_print);
	ft_putnbr_fd(get_time() - data->start_time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(id, 1);
	if (msg == 0)
		ft_putendl_fd(M" has taken a fork"RS, 1);
	if (msg == 1)
		ft_putendl_fd(G" is eating"RS, 1);
	if (msg == 2)
		ft_putendl_fd(Y" is sleeping"RS, 1);
	if (msg == 3)
		ft_putendl_fd(X" is thinking"RS, 1);
	if (msg == 4)
		ft_putendl_fd(R" died"RS, 1);
	pthread_mutex_unlock(&data->mutex_print);
}
