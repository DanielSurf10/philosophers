/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:12:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/12 23:14:16 by danbarbo         ###   ########.fr       */
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
	int				eat_count;
	int				max_eat_count;
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
	pthread_mutex_t	*rigth_fork_mutex;
	pthread_mutex_t	*left_philo_mutex;			// Ponteiro para um mutex do philo da esquerda
	pthread_mutex_t	*rigth_philo_mutex;			// Ponteiro para um mutex do philo da direita
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

#endif
