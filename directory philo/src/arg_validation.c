/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:13:05 by danbarbo          #+#    #+#             */
/*   Updated: 2024/06/16 12:12:16 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!str || !str[0])
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9') || num < 0)
			return (-1);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num < 0)
		return (-1);
	return (num);
}

t_main_data	get_data(char **argv)
{
	t_main_data	data;

	memset(&data, 0, sizeof(t_main_data));
	data.philos_count = ft_atoi(argv[1]);
	data.time_to_die = ft_atoi(argv[2]);
	data.time_to_eat = ft_atoi(argv[3]);
	data.time_to_sleep = ft_atoi(argv[4]);
	data.max_eat_count = argv[5] ? ft_atoi(argv[5]) : -1;
	data.max_eat_count = ternary(argv[5] != NULL, ft_atoi(argv[5]), -1);
	gettimeofday(&data.start, NULL);
	if (data.philos_count == -1 || data.time_to_die == -1
		|| data.time_to_eat == -1 || data.time_to_sleep == -1
		|| (argv[5] && data.max_eat_count == -1))
		data.is_valid = 0;
	else
		data.is_valid = 1;
	return (data);
}
