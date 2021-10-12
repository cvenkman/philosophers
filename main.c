#include "philo.h"

// void threads()
// {
// 	pthread_t t1, t2;

// 	// char *str1 = "1_1_1_1_1\n";
// 	// char *str2 = "2_2_2_2_2\n";
// 	pthread_mutex_init(&mutex, NULL);
// 	pthread_create(&t1, NULL, print, (void *)str1);
// 	// pthread_detach(t1);
// 	pthread_create(&t2, NULL, print, (void *)str2);
// 	// pthread_detach(t2);
// 	pthread_join(t1, NULL);
// 	pthread_join(t2, NULL);
// 	// usleep
// 	write(1, "EX\n", 3);
// }

// int ft_philo()
// {
// 	static int i;

// 	pthread_mutex_lock(mutex);
// 	i++;
// 	printf("ass #%d\n", i);
// 	pthread_mutex_unlock(mutex);
	
// 	return (0);
// }


void print_message(pthread_mutex_t *mutex_print, t_data *data, int id, char *msg)
{
	// pthread_mutex_lock(&(data->mutex_print));
	pthread_mutex_lock(mutex_print);
	printf("%u %d %s\n", (get_time() - data->start_time), id, msg);
	pthread_mutex_unlock(mutex_print);
	// pthread_mutex_unlock(&(data->mutex_print));
}

void ft_eat()
{
	
}

void start(t_data *data)
{
	
}

int philo_create(int nbr_of_philo, t_data *data)
{
	int					i;
	int					ret;
	pthread_t			philo[nbr_of_philo];
	pthread_mutex_t		mutex;

	i = 0;
	data->start_time = get_time();
	while (i < nbr_of_philo)
	{
		if (pthread_create(&(philo[i]), NULL, (void *)start, data) == -1)
		{
			write(2, "failed to create philo live as thread\n", 39);
			return (-1);
		}
		usleep(10000);
		i++;
	}
	return (0);
}
int main(int argc, char **argv)
{
	t_data		data;
	int			i = 1;
	pthread_mutex_t mutex_print;

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
	while (i < data.nbr_of_philo)
	{
		data.philos[i].id = i;
		i++;
	}
	if (philo_create(data.nbr_of_philo, &data) != 0)
		return (-1);
	print_message(&mutex_print, &data, data.philos[3].id, EAT);
}
