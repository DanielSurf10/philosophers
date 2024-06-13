/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:19:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/13 01:34:05 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// ./philo <philo_number> <time_to_die> <time_to_eat> <time_to_sleep> [max_eat]

int	main(int argc, char *argv[])
{
	int			i;
	t_main_data	data;

	const int	philo_count = 4;
	const int	time_to_die = 410;
	const int	time_to_eat = 200;
	const int	time_to_sleep = 200;
	const int	max_eat_count = 7;

	memset(&data, 0, sizeof(t_main_data));
	data.philos_count = philo_count;			// Mudar aqui para pegar do argv já validado
	gettimeofday(&data.start, NULL);
	pthread_mutex_init(&data.print_mutex, NULL);

	data.waiter.forks = malloc(sizeof(int) * data.philos_count);
	memset(data.waiter.forks, 0, sizeof(int) * data.philos_count);

	data.philos = malloc(sizeof(t_philo) * data.philos_count);
	memset(data.philos, 0, sizeof(t_philo) * data.philos_count);

	data.waiter.forks_mutex = malloc(sizeof(pthread_mutex_t) * data.philos_count);

	i = 0;
	while (i < data.philos_count)
	{
		pthread_mutex_init(&data.waiter.forks_mutex[i], NULL);
		pthread_mutex_init(&data.philos[i].philo_mutex, NULL);
		i++;
	}

	i = 0;
	while (i < data.philos_count)
	{
		// ID
		data.philos[i].id = i;

		// Pegar do argv
		data.philos[i].time_to_eat = time_to_eat;			// Mudar aqui para pegar do argv já validado
		data.philos[i].time_to_sleep = time_to_sleep;
		data.philos[i].max_eat_count = max_eat_count;

		// eat count
		data.philos[i].left_philo_eat_count = &data.philos[(i + data.philos_count - 1) % data.philos_count].eat_count;
		data.philos[i].right_philo_eat_count = &data.philos[i].eat_count;

		// Forks
		data.philos[i].left_fork = &data.waiter.forks[(i + data.philos_count - 1) % data.philos_count];
		data.philos[i].right_fork = &data.waiter.forks[i];

		// Começo da simulação
		data.philos[i].start = data.start;
		data.philos[i].last_eat = data.start;

		// Mutex
		data.philos[i].print = &data.print_mutex;
		data.philos[i].left_fork_mutex = &data.waiter.forks_mutex[(i + data.philos_count - 1) % data.philos_count];
		data.philos[i].right_fork_mutex = &data.waiter.forks_mutex[i];
		data.philos[i].left_philo_mutex = &data.philos[(i + data.philos_count - 1) % data.philos_count].philo_mutex;
		data.philos[i].right_philo_mutex = &data.philos[i].philo_mutex;

		pthread_create(&data.philos[i].thread, NULL, philosopher, &data.philos[i]);
		usleep(100);
		i++;
	}

	i = 0;
	while (i < data.philos_count)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}

	pthread_mutex_destroy(&data.print_mutex);

	i = 0;
	while (i < data.philos_count)
	{
		pthread_mutex_destroy(&data.waiter.forks_mutex[i]);
		pthread_mutex_destroy(&data.philos[i].philo_mutex);
		i++;
	}

	free(data.waiter.forks);
	free(data.waiter.forks_mutex);
	free(data.philos);

	return (0);
}
