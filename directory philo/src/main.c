/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 22:19:55 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/08 22:38:42 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *philosopher(void *arg __attribute__((unused)))
{
	printf("Philosopher is eating\n");
	printf("Philosopher is sleeping\n");
	printf("Philosopher is thinking\n");
	return (NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t	thread;

	pthread_create(&thread, NULL, philosopher, NULL);
	pthread_join(thread, NULL);

	return (0);
}
