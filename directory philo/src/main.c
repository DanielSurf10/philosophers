/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:19:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/08 23:44:53 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philosopher(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *) arg;
	pthread_mutex_lock(philo.print);
	printf("Philosopher %i is eating\n", philo.id);
	printf("Philosopher %i is sleeping\n", philo.id);
	printf("Philosopher %i is thinking\n", philo.id);
	pthread_mutex_unlock(philo.print);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int				philos_count = 5;
	t_philo			philos[philos_count];
	pthread_t		thread[philos_count];
	pthread_mutex_t	print_mutex;

	pthread_mutex_init(&print_mutex, NULL);

	for (int i = 0; i < philos_count; i++)
	{
		philos[i].id = i + 1;
		philos[i].print = &print_mutex;
		pthread_create(&thread[i], NULL, philosopher, &philos[i]);
	}

	for (int i = 0; i < philos_count; i++)
	{
		pthread_join(thread[i], NULL);
	}

	pthread_mutex_destroy(&print_mutex);

	return (0);
}
