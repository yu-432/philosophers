/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:07:49 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/06 16:51:36 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_count_eat(t_philo *philos)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	else
	{
		while (i < philos[0].num_of_philos)
		{
			if (philos[i].meals_eaten == philos[0].num_times_to_eat)
				count++;
			i++;
		}
		if (count == philos[0].num_of_philos)
		{
			mutex_func(&philos[0].data->dead_lock, &philos[0], LOCK);
			philos[0].data->is_dead = true;
			mutex_func(&philos[0].data->dead_lock, &philos[0], UNLOCK);
			return (1);
		}
	}
	return (0);
}

int	dead_loop(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (get_time() - philos[i].last_meal > philos[i].time_to_die)
		{
			mutex_func(&philos[0].data->dead_lock, &philos[0], LOCK);
			philos[0].data->is_dead = true;
			mutex_func(&philos[0].data->dead_lock, &philos[0], UNLOCK);
			printf("%0.10zu %d dead\n", get_time() - philos[i].start_time, \
					philos[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*w_routine(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (!philos[0].data->is_dead)
	{
		if (dead_loop(philos) == 1 || check_count_eat(philos) == 1)
			break ;
	}
	return (pointer);
}
