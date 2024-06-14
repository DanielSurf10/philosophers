/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:12:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/13 16:29:49 by danbarbo         ###   ########.fr       */
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

typedef struct timeval t_timeval;

typedef struct s_philo
{
	int				id;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;				// Se eat_count == max_eat -> Não precisa ver se morreu, pq ele já acabou
	int				eat_count;
	int				*left_philo_eat_count;		// Ponteiro para o eat count do philo da esquerda
	int				*right_philo_eat_count;		// Ponteiro para o eat count do philo da direita
	int				*left_fork;
	int				*right_fork;				// Ponteiro para um fork do array de forks
	t_timeval		start;
	t_timeval		last_eat;
	pthread_t		thread;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*print;
	pthread_mutex_t	*left_fork_mutex;			// Ponteiro para um mutex do array de mutex dos forks
	pthread_mutex_t	*right_fork_mutex;
	pthread_mutex_t	*left_philo_mutex;			// Ponteiro para um mutex do philo da esquerda
	pthread_mutex_t	*right_philo_mutex;			// Ponteiro para um mutex do philo da direita
}	t_philo;

typedef struct s_waiter
{
	int				*forks;					// Array de forks
	pthread_mutex_t	*forks_mutex;			// Array de mutex dos forks
}	t_waiter;

typedef struct s_main_data
{
	int				philos_count;
	t_timeval		start;
	t_philo			*philos;
	t_waiter		waiter;
	pthread_mutex_t	print_mutex;
}	t_main_data;

// philospher function
void	*philosopher(void *arg);

// philosophers actions
void	wait_for_adjacent_philosophers_to_eat(t_philo *philo);
void	wait_for_getting_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	start_to_think(t_philo *philo);

// utils
void	print_ms(t_timeval now, t_timeval start);

#endif
