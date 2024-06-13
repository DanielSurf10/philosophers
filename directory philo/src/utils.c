/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:55:05 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/13 00:55:18 by danbarbo         ###   ########.fr       */
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
