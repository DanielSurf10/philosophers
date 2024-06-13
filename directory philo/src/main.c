/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:19:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/12 23:06:32 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_ms(t_timeval now, t_timeval start)
{
	long int	microseconds_now;
	long int	microseconds_since_start;
	long int	miliseconds_since_start;

	microseconds_now = (now.tv_sec * 1000000) + now.tv_usec;
	microseconds_since_start = microseconds_now - ((start.tv_sec * 1000000) + start.tv_usec);
	miliseconds_since_start = microseconds_since_start / 1000;
	printf("%li ", miliseconds_since_start);
}

void	*philosopher(void *arg)
{
	int				get_forks;
	long int		microseconds_since_start;
	long int		microseconds_now;
	t_philo			philo;
	t_timeval		now;
	t_timeval		start;

	philo = *(t_philo *) arg;

	get_forks = 0;
	while (get_forks == 0)
	{
		pthread_mutex_lock(philo.left_fork_mutex);
		pthread_mutex_lock(philo.rigth_fork_mutex);
		if (*philo.left_fork == 0 && *philo.right_fork == 0)
		{
			*philo.left_fork = 1;
			*philo.right_fork = 1;
			get_forks = 1;
		}
		pthread_mutex_unlock(philo.rigth_fork_mutex);
		pthread_mutex_unlock(philo.left_fork_mutex);
		usleep(50);
	}

	gettimeofday(&now, NULL);
	start = philo.start;
	pthread_mutex_lock(philo.print);
	print_ms(now, start);
	printf("Philosopher %i is eating\n", philo.id + 1);
	pthread_mutex_unlock(philo.print);
	usleep(200000);
	pthread_mutex_lock(philo.left_fork_mutex);
	pthread_mutex_lock(philo.rigth_fork_mutex);
	*philo.left_fork = 0;
	*philo.right_fork = 0;
	pthread_mutex_unlock(philo.rigth_fork_mutex);
	pthread_mutex_unlock(philo.left_fork_mutex);

	gettimeofday(&now, NULL);
	pthread_mutex_lock(philo.print);
	print_ms(now, start);
	printf("Philosopher %i is thinking\n", philo.id + 1);
	pthread_mutex_unlock(philo.print);

	return (NULL);
}

int	main(int argc, char *argv[])
{
	int				philos_count = 2;
	t_timeval		start;
	t_philo			philos[philos_count];
	// pthread_t		thread[philos_count];
	pthread_mutex_t	print_mutex;
	t_waiter		waiter;

	pthread_mutex_init(&print_mutex, NULL);
	gettimeofday(&start, NULL);

	waiter.forks = malloc(sizeof(int) * philos_count);
	memset(waiter.forks, 0, sizeof(int) * philos_count);

	waiter.forks_mutex = malloc(sizeof(pthread_mutex_t) * philos_count);

	for (int i = 0; i < philos_count; i++)
	{
		// waiter.forks[i] = i;
		pthread_mutex_init(&waiter.forks_mutex[i], NULL);
	}

	for (int i = 0; i < philos_count; i++)
	{
		philos[i].id = i;
		philos[i].print = &print_mutex;
		philos[i].start = start;
		philos[i].left_fork = &waiter.forks[(i + philos_count - 1) % philos_count];
		philos[i].right_fork = &waiter.forks[i];
		philos[i].left_fork_mutex = &waiter.forks_mutex[(i + philos_count - 1) % philos_count];
		philos[i].rigth_fork_mutex = &waiter.forks_mutex[i];

		pthread_create(&philos[i].thread, NULL, philosopher, &philos[i]);
		usleep(100);
	}

	for (int i = 0; i < philos_count; i++)
	{
		pthread_join(philos[i].thread, NULL);
	}

	pthread_mutex_destroy(&print_mutex);

	for (int i = 0; i < philos_count; i++)
	{
		pthread_mutex_destroy(&waiter.forks_mutex[i]);
	}

	free(waiter.forks);

	return (0);
}
