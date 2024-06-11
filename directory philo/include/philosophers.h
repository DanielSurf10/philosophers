/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:12:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/11 11:55:16 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct timeval t_timeval;

typedef struct s_philo
{
	int				id;
	int				*left_fork;			// Ponteiro pra um fork do array de forks
	int				*right_fork;
	pthread_mutex_t	*print;
	struct timeval	start;
}	t_philo;

typedef struct s_waiter
{
	int		*forks;		// Array de forks
}	t_waiter;

#endif
