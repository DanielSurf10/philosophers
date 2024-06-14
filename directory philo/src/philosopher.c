/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:13:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/14 00:03:27 by danbarbo         ###   ########.fr       */
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
	while ((cycle_count < philo->max_eat_count || philo->max_eat_count == -1) && someone_died == 0)
	{

		wait_for_adjacent_philosophers_to_eat(philo);

		wait_for_getting_forks(philo);

		gettimeofday(&now, NULL);

		pthread_mutex_lock(&philo->philo_mutex);
		philo->last_eat = now;
		someone_died = *philo->someone_died;
		pthread_mutex_unlock(&philo->philo_mutex);

		// Antes de comer, verificar se não morreu
		if (someone_died == 0)
			eat(philo);

		pthread_mutex_lock(&philo->philo_mutex);
		philo->eat_count++;
		cycle_count++;
		someone_died = *philo->someone_died;
		pthread_mutex_unlock(&philo->philo_mutex);

		if (someone_died == 0)
			philo_sleep(philo);

		pthread_mutex_lock(&philo->philo_mutex);
		someone_died = *philo->someone_died;
		pthread_mutex_unlock(&philo->philo_mutex);

		if (someone_died == 0)
			start_to_think(philo);

	}

	return (NULL);
}
