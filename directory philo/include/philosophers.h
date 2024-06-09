/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:12:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/08 23:27:28 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	// int				left_fork;
	// int				right_fork;
	// int				times_to_eat;
	// int				eat_count;
	// long long		last_eat;
	// pthread_t		thread;
	// pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	// pthread_mutex_t	*death;
}	t_philo;

#endif
