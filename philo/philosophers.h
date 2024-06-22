/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:12:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/21 14:11:29 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define RST	"\001\033[0m\002"
# define ORANGE	"\001\033[38;5;208m\002"
# define BLUE	"\001\033[38;5;27m\002"
# define GREEN	"\001\033[38;5;46m\002"
# define RED	"\001\033[38;5;196m\002"
# define YELLOW	"\001\033[38;5;226m\002"
# define CYAN	"\001\033[38;5;51m\002"
# define PURPLE	"\001\033[38;5;129m\002"
# define GREY	"\001\033[38;5;240m\002"
# define WHITE	"\001\033[38;5;231m\002"
# define BLACK	"\001\033[38;5;16m\002"
# define BOLD	"\001\033[1m\002"
# define UNDER	"\001\033[4m\002"
# define BLINK	"\001\033[5m\002"
# define RST	"\001\033[0m\002"

// # define ORANGE	""
// # define BLUE	""
// # define GREEN	""
// # define RED	""
// # define YELLOW	""
// # define CYAN	""
// # define PURPLE	""
// # define GREY	""
// # define WHITE	""
// # define BLACK	""
// # define BOLD	""
// # define UNDER	""
// # define BLINK	""
// # define RST	""

enum e_status
{
	GET_FORK,
	EATING,
	THINK,
	SLEEP,
};

typedef struct timeval	t_timeval;

typedef struct s_philo
{
	int				id;
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;
	int				eat_count;
	int				*someone_died;
	t_timeval		start;
	t_timeval		last_eat;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*left_fork_mutex;
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*someone_died_mutex;
}	t_philo;

typedef struct s_main_data
{
	int				is_valid;
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;
	int				someone_died;
	t_philo			*philos;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	someone_died_mutex;
	t_timeval		start;
}	t_main_data;

// philospher function
void		*philosopher(void *arg);

// philosophers actions
void		get_forks(t_philo *philo);
void		eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		think(t_philo *philo);

// die logic
void		wait_until_someone_finish_or_die(t_main_data *data);

// validation
t_main_data	get_data(char **argv);

// utils
void		print_ms(t_timeval now, t_timeval start);
int			ternary(int condition, int if_true, int if_false);
void		print_color(char *color);

// print mutex
void		print_mutex(t_philo *philo, int status);
void		print_mutex_get_fork(t_philo *philo);
void		print_mutex_eating(t_philo *philo);
void		print_mutex_sleep(t_philo *philo);
void		print_mutex_think(t_philo *philo);

#endif
