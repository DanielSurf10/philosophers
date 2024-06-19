/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:33:49 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/19 20:34:06 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_mutex_get_fork(t_philo *philo)
{
	printf(PURPLE"%i"RST" has "GREY"taken a fork\n"RST, philo->id + 1);
}

void	print_mutex_eating(t_philo *philo)
{
	printf(PURPLE"%i"RST" is "ORANGE"eating\n"RST, philo->id + 1);
}

void	print_mutex_sleep(t_philo *philo)
{
	printf(PURPLE"%i"RST" is "BLUE"sleeping\n"RST, philo->id + 1);
}

void	print_mutex_think(t_philo *philo)
{
	printf(PURPLE"%i"RST" is "YELLOW"thinking\n"RST, philo->id + 1);
}
