/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:23:12 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/14 03:15:41 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	my_sleep(unsigned long time)
{
	unsigned long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(200);
}
static int	ft_lenn(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_putnbr(int n, char (*str)[10])
{
	int		i;
	int		a;

	i = ft_lenn(n) - 1;
	a = i + 1;
	while (n > 0)
	{
		(*str)[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	(*str)[a] = '\0';
}

int get_msg_complete(char (*msg_complete)[50], t_data *data, int id, char *msg)
{
	int		i;
	int		a;
	char	num_str[10];
	char	id_str[10];

	ft_putnbr(get_time() - data->start_time, &num_str);
	i = -1;
	while (num_str[++i])
		(*msg_complete)[i] = num_str[i];
	(*msg_complete)[i++] = ' ';
	ft_putnbr(id, &id_str);
	a = -1;
	while (id_str[++a])
		(*msg_complete)[i++] = id_str[a];
	a = 0;
	while (msg[a])
		(*msg_complete)[i++] = msg[a++];
	(*msg_complete)[i++] = '\n';
	return (i);
}

void	print_message(t_data *data, int id, char *msg)
{
	char	msg_complete[50];
	int		msg_len;

	msg_len = get_msg_complete(&msg_complete, data, id, msg);
	pthread_mutex_lock(&data->mutex_print);
	write(1, msg_complete, msg_len);
	pthread_mutex_unlock(&data->mutex_print);
}
