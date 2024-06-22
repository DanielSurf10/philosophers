/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:54:50 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/21 14:13:18 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_someone_died(t_philo *philo)
{
	int	someone_died;

	pthread_mutex_lock(&philo->philo_mutex);
	pthread_mutex_lock(philo->someone_died_mutex);
	someone_died = *philo->someone_died;
	pthread_mutex_unlock(philo->someone_died_mutex);
	pthread_mutex_unlock(&philo->philo_mutex);
	return (someone_died);
}

void	print_mutex(t_philo *philo, int status)
{
	int			someone_died;
	t_timeval	now;
	t_timeval	start;

	gettimeofday(&now, NULL);
	start = philo->start;
	someone_died = get_someone_died(philo);
	if (someone_died == 0)
	{
		pthread_mutex_lock(philo->print);
		if (isatty(STDOUT_FILENO))
			print_color(CYAN);
		print_ms(now, start);
		if (isatty(STDOUT_FILENO))
			print_color(RST);
		if (status == GET_FORK)
			print_mutex_get_fork(philo);
		else if (status == EATING)
			print_mutex_eating(philo);
		else if (status == SLEEP)
			print_mutex_sleep(philo);
		else if (status == THINK)
			print_mutex_think(philo);
		pthread_mutex_unlock(philo->print);
	}
}
