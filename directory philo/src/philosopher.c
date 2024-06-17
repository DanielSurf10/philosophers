/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:13:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/17 20:07:14 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher(void *arg)
{
	int				cycle_count;
	int				someone_died;
	t_philo			*philo;
	t_timeval		now;

	philo = (t_philo *) arg;
	cycle_count = 0;
	someone_died = 0;
	while ((cycle_count < philo->max_eat_count || philo->max_eat_count == -1)
		&& someone_died == 0 && philo->philos_count > 1)
	{
		// pthread_mutex_lock(&philo->philo_mutex);
		// gettimeofday(&philo->now, NULL);
		// pthread_mutex_unlock(&philo->philo_mutex);

		get_forks(philo);

		pthread_mutex_lock(&philo->philo_mutex);
		gettimeofday(&philo->last_eat, NULL);
		pthread_mutex_unlock(&philo->philo_mutex);

		eat(philo);

		// pthread_mutex_lock(&philo->philo_mutex);
		// gettimeofday(&philo->now, NULL);
		// pthread_mutex_unlock(&philo->philo_mutex);

		philo_sleep(philo);

		// pthread_mutex_lock(&philo->philo_mutex);
		// gettimeofday(&philo->now, NULL);
		// pthread_mutex_unlock(&philo->philo_mutex);

		think(philo);

		pthread_mutex_lock(&philo->philo_mutex);
		someone_died = *philo->someone_died;
		philo->eat_count++;
		pthread_mutex_unlock(&philo->philo_mutex);

		cycle_count++;
	}

	return (NULL);
}
