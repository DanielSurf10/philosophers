/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:19:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/20 17:25:24 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// ./philo <philo_number> <time_to_die> <time_to_eat> <time_to_sleep> [max_eat]

t_main_data	validate_args(int argc, char *argv[])
{
	t_main_data	data;

	if (!(argc >= 5 && argc <= 6))
	{
		write(2, "Invalid argument number!\n", 25);
		exit(1);
	}
	data = get_data(argv);
	if (data.is_valid == 0)
	{
		write(2, "Invalid arguments!\n", 19);
		exit(1);
	}
	return (data);
}

void	init_philos(t_main_data	*data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].id = i;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].max_eat_count = data->max_eat_count;
		data->philos[i].someone_died = &data->someone_died;
		data->philos[i].start = data->start;
		data->philos[i].last_eat = data->start;
		data->philos[i].print = &data->print_mutex;
		data->philos[i].left_fork_mutex = \
	&data->forks_mutex[(i + data->philos_count - 1) % data->philos_count];
		data->philos[i].right_fork_mutex = &data->forks_mutex[i];
		data->philos[i].someone_died_mutex = &data->someone_died_mutex;
		data->philos[i].philos_count = data->philos_count;
		pthread_create(&data->philos[i].thread, NULL, philosopher, \
			&data->philos[i]);
		usleep(500);
		i++;
	}
}

void	philos_init(t_main_data	*data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philos_count);
	memset(data->philos, 0, sizeof(t_philo) * data->philos_count);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->someone_died_mutex, NULL);
	data->forks_mutex = malloc(sizeof(pthread_mutex_t) * data->philos_count);
	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_init(&data->forks_mutex[i], NULL);
		pthread_mutex_init(&data->philos[i].philo_mutex, NULL);
		i++;
	}
	init_philos(data);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_main_data	data;

	data = validate_args(argc, argv);
	philos_init(&data);
	wait_until_someone_finish_or_die(&data);
	i = 0;
	while (i < data.philos_count)
	{
		pthread_join(data.philos[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&data.print_mutex);
	pthread_mutex_destroy(&data.someone_died_mutex);
	i = 0;
	while (i < data.philos_count)
	{
		pthread_mutex_destroy(&data.forks_mutex[i]);
		pthread_mutex_destroy(&data.philos[i].philo_mutex);
		i++;
	}
	free(data.forks_mutex);
	free(data.philos);
	return (0);
}
