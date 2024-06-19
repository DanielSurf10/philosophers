/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_logic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 22:24:26 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/18 23:55:40 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_philo_died(t_philo *philo)
{
	long int	milliseconds_now;
	long int	milliseconds_last_meal;
	long int	milliseconds_since_last_meal;
	t_timeval	now;

	gettimeofday(&now, NULL);
	milliseconds_now = (now.tv_sec * 1000000 + now.tv_usec) / 1000;
	milliseconds_last_meal = (philo->last_eat.tv_sec * 1000000
			+ philo->last_eat.tv_usec) / 1000;
	milliseconds_since_last_meal = milliseconds_now - milliseconds_last_meal;
	if (milliseconds_since_last_meal > philo->time_to_die
		&& (philo->eat_count < philo->max_eat_count
			|| philo->max_eat_count == -1))
	{
		pthread_mutex_lock(philo->print);
		print_color(CYAN);
		print_ms(now, philo->start);
		print_color(RST);
		printf(YELLOW"%d"RED" died\n"RST, philo->id + 1);
		pthread_mutex_unlock(philo->print);
		return (1);
	}
	return (0);
}

void	wait_until_someone_finish_or_die(t_main_data *data)
{
	int	i;
	int	someone_died;
	int	everyone_finished_eating;

	someone_died = 0;
	everyone_finished_eating = 0;
	while (someone_died == 0 && everyone_finished_eating == 0)
	{
		i = 0;
		everyone_finished_eating = 1;
		while (i < data->philos_count && someone_died == 0)
		{
			pthread_mutex_lock(&data->philos[i].philo_mutex);
			if (is_philo_died(&data->philos[i]))
			{
				data->someone_died = 1;
				someone_died = 1;
			}
			if (data->philos[i].eat_count < data->philos[i].max_eat_count
				|| data->philos[i].max_eat_count == -1)
				everyone_finished_eating = 0;
			pthread_mutex_unlock(&data->philos[i++].philo_mutex);
		}
		usleep(500); // Talvez aqui mude
	}
}
