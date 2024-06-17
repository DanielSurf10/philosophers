/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:12:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/16 12:26:35 by danbarbo         ###   ########.fr       */
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

enum e_status
{
	EAT,
	THINK,
	SLEEP
};

typedef struct timeval t_timeval;

typedef struct s_philo
{
	int				id;
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;				// Se eat_count == max_eat -> Não precisa ver se morreu, pq ele já acabou
	int				eat_count;
	// int				*left_philo_eat_count;		// Ponteiro para o eat count do philo da esquerda
	// int				*right_philo_eat_count;		// Ponteiro para o eat count do philo da direita
	// int				*left_fork;
	// int				*right_fork;				// Ponteiro para um fork do array de forks
	int				*someone_died;
	t_timeval		start;
	t_timeval		last_eat;
	// t_timeval		now;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*left_fork_mutex;			// Ponteiro para um mutex do array de mutex dos forks
	pthread_mutex_t	*right_fork_mutex;
	// pthread_mutex_t	*left_philo_mutex;			// Ponteiro para um mutex do philo da esquerda
	// pthread_mutex_t	*right_philo_mutex;			// Ponteiro para um mutex do philo da direita
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
	// int				*forks;					// Array de forks
	t_philo			*philos;
	pthread_mutex_t	*forks_mutex;			// Array de mutex dos forks
	pthread_mutex_t	print_mutex;
	t_timeval		start;
}	t_main_data;

// philospher function
void	*philosopher(void *arg);

// philosophers actions
// void	wait_for_adjacent_philosophers_to_eat(t_philo *philo);
void	get_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

// die logic
void	wait_until_someone_finish_or_die(t_main_data *data);

// validation
t_main_data	get_data(char **argv);

// utils
void	print_ms(t_timeval now, t_timeval start);
void	print_mutex(t_philo *philo, int status);
int		ternary(int condition, int if_true, int if_false);

#endif
