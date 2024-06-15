/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:54:17 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/15 16:17:11 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork_mutex);
	print_mutex(philo, EAT);
	pthread_mutex_lock(philo->right_fork_mutex);
	print_mutex(philo, EAT);
}

void	eat(t_philo *philo)
{
// 	t_timeval	now;
// 	t_timeval	start;
//
// 	pthread_mutex_lock(&philo->philo_mutex);
// 	now = philo->now;
// 	start = philo->start;
// 	philo->last_eat = philo->now;
// 	pthread_mutex_unlock(&philo->philo_mutex);
//
// 	pthread_mutex_lock(philo->print);
// 	print_ms(now, start);
// 	printf("%i taken a fork\n", philo->id + 1);
// 	print_ms(now, start);
// 	printf("%i taken a fork\n", philo->id + 1);
// 	pthread_mutex_unlock(philo->print);
//
// 	print_mutex(philo, EAT);

	usleep(philo->time_to_eat * 1000);

	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
}

void	philo_sleep(t_philo *philo)
{
// 	t_timeval	now;
// 	t_timeval	start;
//
// 	pthread_mutex_lock(&philo->philo_mutex);
// 	now = philo->now;
// 	start = philo->start;
// 	pthread_mutex_unlock(&philo->philo_mutex);
//
// 	pthread_mutex_lock(philo->print);
// 	print_ms(now, start);
// 	printf("%i is sleeping\n", philo->id + 1);
// 	pthread_mutex_unlock(philo->print);

	print_mutex(philo, SLEEP);
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
// 	t_timeval	now;
// 	t_timeval	start;
//
// 	pthread_mutex_lock(&philo->philo_mutex);
// 	now = philo->now;
// 	start = philo->start;
// 	pthread_mutex_unlock(&philo->philo_mutex);
//
// 	pthread_mutex_lock(philo->print);
// 	print_ms(now, philo->start);
// 	printf("%i is thinking\n", philo->id + 1);
// 	pthread_mutex_unlock(philo->print);

	print_mutex(philo, THINK);
}
