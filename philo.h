#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft/libft.h"

#define FORK	0
#define EAT 	1
#define SLEEP 	2
#define THINK	3
#define DIE		4

# define R	"\x1b[31m"
# define G	"\x1b[32m"
# define Y	"\x1b[33m"
# define M  "\x1b[35m"
# define X  "\x1b[36m"
# define RS	"\x1b[0m"

struct	s_data;

typedef struct s_philo
{
	unsigned int	limit_time;
	unsigned int	start_time_eat;
	int				id;
	int				l_fork;
	int				r_fork;
	pthread_t		thread;
	// int				eat_now;
	int				done;
	int				eat_count;
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
	t_philo				*philos;
	pthread_mutex_t		to_do;
	pthread_t			monitor;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		check_dead;
	pthread_mutex_t		eat_check;
}						t_data;

unsigned int	get_time(void);
int				init_mutex(t_data *data);
void			my_sleep(long int time);
void			print_message(t_data *data, int id, int msg);
void			init_philos(t_data *data);

#endif
