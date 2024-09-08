/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:07:49 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/08 19:59:27 by yooshima         ###   ########.fr       */
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
			pthread_mutex_lock(philos[i].write_lock);
			if (philos[i].meals_eaten >= philos[0].num_times_to_eat)
				count++;
			pthread_mutex_unlock(philos[i].write_lock);
			i++;
		}
		if (count == philos[0].num_of_philos)
		{
			pthread_mutex_lock(philos[0].dead_lock);
			*philos[0].is_dead = true;
			return (pthread_mutex_unlock(philos[0].dead_lock), 1);
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
		pthread_mutex_lock(philos[i].write_lock);
		if (get_time() - philos[i].last_meal > philos[i].time_to_die)
		{
			pthread_mutex_unlock(philos[i].write_lock);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos[0].is_dead = true;
			pthread_mutex_unlock(philos[0].dead_lock);
			printf("%zu %d died\n", get_time() - philos[i].start_time, \
					philos[i].id);
			return (1);
		}
		pthread_mutex_unlock(philos[i].write_lock);
		i++;
	}
	return (0);
}

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (false);
}

void	*w_routine(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (dead_loop(philos) == 1 || check_count_eat(philos) == 1 \
			|| is_dead(&philos[0]))
			break ;
	}
	return (pointer);
}
