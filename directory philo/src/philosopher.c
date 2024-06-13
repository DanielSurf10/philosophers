/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:13:14 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/13 01:22:28 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*philosopher(void *arg)
{
	int				cycle_count;
	t_philo			philo;
	t_timeval		now;

	philo = *(t_philo *) arg;

	cycle_count = 0;
	while (cycle_count < philo.max_eat_count || philo.max_eat_count == -1)
	{
		wait_for_adjacent_philosophers_to_eat(&philo);

		wait_for_getting_forks(&philo);

		gettimeofday(&now, NULL);
		pthread_mutex_lock(&philo.philo_mutex);
		philo.last_eat = now;
		pthread_mutex_unlock(&philo.philo_mutex);

		// Antes de comer, verificar se não morreu
		eat(&philo);

		philo_sleep(&philo);

		start_to_think(&philo);
		cycle_count++;
	}

	return (NULL);
}
