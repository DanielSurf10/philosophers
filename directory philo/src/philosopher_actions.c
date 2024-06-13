/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:54:17 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/13 01:26:28 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_for_adjacent_philosophers_to_eat(t_philo *philo)
{
	int	adjacent_philosophers_have_eaten;

	adjacent_philosophers_have_eaten = 0;
	while (adjacent_philosophers_have_eaten == 0)
	{
		pthread_mutex_lock(&philo->philo_mutex);
		pthread_mutex_lock(philo->left_philo_mutex);
		pthread_mutex_lock(philo->right_philo_mutex);

		if (*philo->left_philo_eat_count >= philo->eat_count
			&& *philo->right_philo_eat_count >= philo->eat_count)
				adjacent_philosophers_have_eaten = 1;

		pthread_mutex_unlock(philo->right_philo_mutex);
		pthread_mutex_unlock(philo->left_philo_mutex);
		pthread_mutex_unlock(&philo->philo_mutex);
		usleep(50);
	}
}

void	wait_for_getting_forks(t_philo *philo)
{
	int	get_forks;

	get_forks = 0;
	while (get_forks == 0)
	{
		// Ele vai morrer aqui se esperar demais pelo garfo

		pthread_mutex_lock(philo->left_fork_mutex);
		pthread_mutex_lock(philo->right_fork_mutex);
		if (*philo->left_fork == 0 && *philo->right_fork == 0)
		{
			*philo->left_fork = 1;
			*philo->right_fork = 1;
			get_forks = 1;
		}
		pthread_mutex_unlock(philo->right_fork_mutex);
		pthread_mutex_unlock(philo->left_fork_mutex);
		usleep(50);
	}
}

void	eat(t_philo *philo)
{
	t_timeval	now;
	t_timeval	start;

	start = philo->start;
	gettimeofday(&now, NULL);
	pthread_mutex_lock(philo->print);
	print_ms(now, start);
	printf("%i taken a fork\n", philo->id + 1);
	print_ms(now, start);
	printf("%i taken a fork\n", philo->id + 1);
	pthread_mutex_unlock(philo->print);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(philo->left_fork_mutex);
	pthread_mutex_lock(philo->right_fork_mutex);
	*philo->left_fork = 0;
	*philo->right_fork = 0;
	pthread_mutex_unlock(philo->right_fork_mutex);
	pthread_mutex_unlock(philo->left_fork_mutex);
}

void	philo_sleep(t_philo *philo)
{
	t_timeval	now;
	t_timeval	start;

	start = philo->start;
	gettimeofday(&now, NULL);
	pthread_mutex_lock(philo->print);
	print_ms(now, start);
	printf("%i is sleeping\n", philo->id + 1);
	pthread_mutex_unlock(philo->print);
	usleep(philo->time_to_sleep * 1000);
}

void	start_to_think(t_philo *philo)
{
	t_timeval	now;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(philo->print);
	print_ms(now, philo->start);
	printf("%i is thinking\n", philo->id + 1);
	pthread_mutex_unlock(philo->print);
}
