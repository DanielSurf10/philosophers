/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:13:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/20 19:00:43 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_someone_died_and_set_eat_count(t_philo *philo)
{
	int	someone_died;

	pthread_mutex_lock(&philo->philo_mutex);
	pthread_mutex_lock(philo->someone_died_mutex);
	someone_died = *philo->someone_died;
	pthread_mutex_unlock(philo->someone_died_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (someone_died);
}

void	*philosopher(void *arg)
{
	int				cycle_count;
	int				someone_died;
	t_philo			*philo;

	philo = (t_philo *) arg;
	cycle_count = 0;
	someone_died = 0;
	while ((cycle_count < philo->max_eat_count || philo->max_eat_count == -1)
		&& someone_died == 0 && philo->philos_count > 1)
	{
		get_forks(philo);
		pthread_mutex_lock(&philo->philo_mutex);
		gettimeofday(&philo->last_eat, NULL);
		pthread_mutex_unlock(&philo->philo_mutex);
		eat(philo);
		philo_sleep(philo);
		think(philo);
		someone_died = get_someone_died_and_set_eat_count(philo);
		cycle_count++;
	}
	if (philo->philos_count == 1)
		print_mutex(philo, GET_FORK);
	return (NULL);
}
