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

typedef struct s_philo
{
	int				id;
	int				eat_now;
	unsigned int	limit_time;
	unsigned int	start_time_eat;
	int				l_fork;
	int				r_fork;
	int				eat_count;
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
	t_philo philos[200];
	pthread_mutex_t		mutex_print;
}						t_data;

unsigned int	get_time(void);

#endif
