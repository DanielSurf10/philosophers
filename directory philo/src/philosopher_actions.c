/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:54:17 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/18 00:18:58 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_forks(t_philo *philo)
{
	if (philo->id % 2 || philo->philos_count % 2 != 0)
	{
		pthread_mutex_lock(philo->left_fork_mutex);
		print_mutex(philo, GET_FORK);
		pthread_mutex_lock(philo->right_fork_mutex);
		print_mutex(philo, GET_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork_mutex);
		print_mutex(philo, GET_FORK);
		pthread_mutex_lock(philo->left_fork_mutex);
		print_mutex(philo, GET_FORK);
	}
}

void	eat(t_philo *philo)
{
	print_mutex(philo, EATING);
	usleep(philo->time_to_eat * 1000);
	if (philo->id % 2 || philo->philos_count % 2 != 0)
	{
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(philo->right_fork_mutex);
	}
}

void	philo_sleep(t_philo *philo)
{
	print_mutex(philo, SLEEP);
	usleep(philo->time_to_sleep * 1000);
}

void	think(t_philo *philo)
{
	print_mutex(philo, THINK);
}
