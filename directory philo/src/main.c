/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:19:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/11 12:51:00 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_ms(t_timeval now, t_timeval start)
{
	long int	microseconds_now;
	long int	microseconds_since_start;

	microseconds_now = (now.tv_sec * 1000000) + now.tv_usec;
	microseconds_since_start = microseconds_now - ((start.tv_sec * 1000000) + start.tv_usec);
	printf("%li ", microseconds_since_start);
}

void	*philosopher(void *arg)
{
	long int		microseconds_since_start;
	long int		microseconds_now;
	t_philo			philo;
	t_timeval		now;
	t_timeval		start;

	philo = *(t_philo *) arg;

	gettimeofday(&now, NULL);
	start = philo.start;

	pthread_mutex_lock(philo.print);
	print_ms(now, start);
	printf("Philosopher %i is eating\n", microseconds_since_start, philo.id);
	pthread_mutex_unlock(philo.print);

// 	gettimeofday(&time, NULL);
// 	microseconds_now = (time.tv_sec * 1000000) + (time.tv_usec);
// 	microseconds_since_start = microseconds_now - ((philo.start.tv_sec * 1000000) + (philo.start.tv_usec));
// 	pthread_mutex_lock(philo.print);
// 	print_ms();
// 	printf("%8li Philosopher %i is eating\n", microseconds_since_start, philo.id);
// 	// pthread_mutex_unlock(philo.print);
// 	usleep(1000000);
//
// 	gettimeofday(&time, NULL);
// 	microseconds_now = (time.tv_sec * 1000000) + (time.tv_usec);
// 	microseconds_since_start = microseconds_now - ((philo.start.tv_sec * 1000000) + (philo.start.tv_usec));
// 	// pthread_mutex_lock(philo.print);
// 	print_ms();
// 	printf("%8li Philosopher %i is sleeping\n", microseconds_since_start, philo.id);
// 	// pthread_mutex_unlock(philo.print);
// 	usleep(2000000);
//
// 	gettimeofday(&time, NULL);
// 	microseconds_now = (time.tv_sec * 1000000) + (time.tv_usec);
// 	microseconds_since_start = microseconds_now - ((philo.start.tv_sec * 1000000) + (philo.start.tv_usec));
// 	// pthread_mutex_lock(philo.print);
// 	print_ms();
// 	printf("%8li Philosopher %i is thinking\n", microseconds_since_start, philo.id);
// 	pthread_mutex_unlock(philo.print);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int				philos_count = 2;
	t_timeval		start;
	t_philo			philos[philos_count];
	pthread_t		thread[philos_count];
	t_waiter		waiter;
	pthread_mutex_t	print_mutex;

	pthread_mutex_init(&print_mutex, NULL);
	gettimeofday(&start, NULL);

	waiter.forks = malloc(sizeof(int) * philos_count);

	for (int i = 0; i < philos_count; i++)
	{
		philos[i].id = i + 1;
		philos[i].print = &print_mutex;
		philos[i].start = start;
		philos[i].left_fork = &waiter.forks[(i + philos_count - 1) % philos_count];
		philos[i].right_fork = i;
		pthread_create(&thread[i], NULL, philosopher, &philos[i]);
	}

	for (int i = 0; i < philos_count; i++)
	{
		pthread_join(thread[i], NULL);
	}

	pthread_mutex_destroy(&print_mutex);

	return (0);
}
