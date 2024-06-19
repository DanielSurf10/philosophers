/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:54:50 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/18 23:51:23 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_mutex_get_fork(t_philo *philo)
{
	printf(PURPLE"%i"RST" has "GREY"taken a fork\n"RST, philo->id + 1);
}

static void	print_mutex_eating(t_philo *philo)
{
	printf(PURPLE"%i"RST" is "ORANGE"eating\n"RST, philo->id + 1);
}

static void	print_mutex_sleep(t_philo *philo)
{
	printf(PURPLE"%i"RST" is "BLUE"sleeping\n"RST, philo->id + 1);
}

static void	print_mutex_think(t_philo *philo)
{
	printf(PURPLE"%i"RST" is "YELLOW"thinking\n"RST, philo->id + 1);
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
		print_color(CYAN);
		print_ms(now, start);
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
