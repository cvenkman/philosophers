/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvenkman <cvenkman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:01:50 by cvenkman          #+#    #+#             */
/*   Updated: 2021/11/11 18:02:55 by cvenkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>
# include "libft/libft.h"

# define FORK	0
# define EAT 	1
# define SLEEP 	2
# define THINK	3
# define R	"\x1b[31m"
# define G	"\x1b[32m"
# define Y	"\x1b[33m"
# define M  "\x1b[35m"
# define X  "\x1b[36m"
# define RS	"\x1b[0m"

struct	s_data;

typedef struct s_philo
{
	unsigned long	last_eat_time;
	unsigned long	start_philo_life;
	int				id;
	int				l_fork;
	int				r_fork;
	pthread_t		thread;
	bool			done;
	int				eat_count;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int					nbr_of_philo;
	unsigned long		live_time;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_philo_must_eat;
	bool				is_nbr_eat;
	bool				end;
	bool				stop;
	int					done;
	unsigned long		start_time;
	pthread_t			monitor;
	pthread_mutex_t		to_do;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		check_dead;
	pthread_mutex_t		eat_check;
	pthread_mutex_t		*forks;
	t_philo				*philos;
}						t_data;

// src/utilsc.
void			my_sleep(unsigned long time);
void			print_message(t_data *data, int id, int msg);
unsigned long	get_time(void);

// src/init.c
int				init_mutex(t_data *data);
int				init_philos(t_data *data);
int				init_argv(int argc, char **argv, t_data *data);

// src/monitor.c
void			*ft_monitor(void *data);

// src/philo.c
void			*start(void *philo_tmp);
#endif
