#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft/libft.h"

#define FORK	"has taken a fork"
#define EAT 	"is eating"
#define SLEEP 	"is sleeping"
#define THINK	"is thinking"
#define DIE		"died"

struct	s_data;

typedef struct s_philo
{
	int				id;
	unsigned int	limit_time;
	unsigned int	start_time_eat;
	int				l_fork;
	int				r_fork;
	pthread_t		thread;
	// int				eat_now;
	// int				eat_count;
	struct s_data	*data;
}					t_philo;

typedef struct	s_data
{
	int					nbr_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_philo_must_eat;
	unsigned int		start_time;
	pthread_mutex_t		*forks;
	// pthread_mutex_t		*r_fork;
	t_philo				*philos;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		check_dead;
}						t_data;

unsigned int	get_time(void);

#endif
