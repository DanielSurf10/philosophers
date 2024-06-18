/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:54:50 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/17 23:18:44 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_mutex_eat(t_philo *philo)
{
	printf("%i has taken a fork\n", philo->id + 1);
}

static void	print_mutex_sleep(t_philo *philo)
{
	printf("%i is sleeping\n", philo->id + 1);
}

static void print_mutex_think(t_philo *philo)
{
	printf("%i is thinking\n", philo->id + 1);
}

static void print_mutex_eating(t_philo *philo)
{
	printf("%i is eating\n", philo->id + 1);
}

void	print_mutex(t_philo *philo, int status)
{
	int			someone_died;
	t_timeval	now;
	t_timeval	start;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->philo_mutex);
	start = philo->start;
	someone_died = *philo->someone_died;
	pthread_mutex_unlock(&philo->philo_mutex);

	if (someone_died == 0)
	{
		pthread_mutex_lock(philo->print);

		print_ms(now, start);

		if (status == EAT)
			print_mutex_eat(philo);
		else if (status == SLEEP)
			print_mutex_sleep(philo);
		else if (status == THINK)
			print_mutex_think(philo);
		else if (status == EATING)
			print_mutex_eating(philo);

		pthread_mutex_unlock(philo->print);

	}
}
