/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:07:49 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/01 13:00:14 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_count_eat(t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philos[0].num_of_philos)
	{
		if (philos[i].meals_eaten == philos[0].time_to_eat)
			count++;
		i++;
	}
	if (count == philos[0].num_of_philos)
		return (1);
	return (0);
}



int	check_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		if (get_time() - philos[i].last_meal > philos[i].time_to_die)
		{
			pthread_mutex_lock(&philos[0].data->dead_lock);
			philos[0].data->is_dead = true;
			printf("%zu %d dead\n", get_time(), i + 1);
			return (pthread_mutex_unlock(&philos[0].data->dead_lock), 1);
		}
		i++;
	}
	return (0);
}

void	*w_routine(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_dead(philos) == 1 || check_count_eat(philos) == 1)
			break ;
	return (NULL);
}