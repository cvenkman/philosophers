#include "philo.h"

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

void my_sleep(long int time)
{
	long int start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(1);
}

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
	my_sleep(philos->data->time_to_sleep);
}

void eat(t_philo *philos)
{
	pthread_mutex_lock(&philos->data->to_do);
	print_message(philos->data, philos->id, EAT);
	philos->eat_count++;
	my_sleep(philos->data->time_to_eat);
	pthread_mutex_unlock(&philos->data->to_do);
}

void *start(void *philos_tmp)
{
	t_philo *philos;
	philos = philos_tmp;

	while (1)
	{
		take_forks(philos);
		eat(philos);
		ft_sleep(philos);
		print_message(philos->data, philos->id, THINK);
	}
	print_message(philos->data, philos->id, EAT);
	return (NULL);
}

void *monitor(void *data_tmp)
{
	t_data	*data;
	int		i;
	int		u;

	data = data_tmp;
	i = 0;
	u = 0;
	// while (i < data->nbr_philo_must_eat)
	// {
		pthread_mutex_lock(&data->eat_check);
		
		while (i <= data->nbr_of_philo)
		{

			if (data->philos[i].eat_count <= data->nbr_philo_must_eat)
			{
				printf("%d %d\n", i, data->nbr_philo_must_eat);
				break ;
			}
			i++;
		}
		if (i == data->nbr_of_philo)
			exit(0);
		pthread_mutex_unlock(&data->eat_check);
	// }

	return (NULL);
}

int philo_create(t_data *data)
{
	int				i;
	int				ret;
	pthread_t		philo[data->nbr_of_philo];
	pthread_t		monitor_id;

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
		my_sleep(1000);
		i++;
	}
	if (pthread_create(&monitor_id, NULL, monitor, (void *)data) == -1)
		return (-1);
	pthread_join(monitor_id, NULL);
	return (0);
}

void init_philos(t_data *data)
{
	int			i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!data->philos)
		return ;
	while (i < data->nbr_of_philo)
	{
		data->philos[i].id = i;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = i + 1;
		if (data->philos[i].r_fork > data->nbr_of_philo - 1)
			data->philos[i].r_fork = 0;
		data->philos[i].data = data;
		data->philos[i].eat_count = 0;
		i++;
	}
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
		return (-1);
	while (i < data->nbr_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
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
	
}
