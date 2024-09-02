/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:07:49 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/02 15:02:23 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_count_eat(t_philo *philos)
{
	int	count;

	count = 0;
	if (philos[0].time_to_eat == -1)
		return(0);
	else if (philos[0].num_of_philos % 2 == 0 && \
		philos[philos[0].num_of_philos - 1].meals_eaten == philos[0].num_times_to_eat)
		{
			pthread_mutex_lock(&philos[0].data->dead_lock);
			philos[0].data->is_dead = true;
			pthread_mutex_unlock(&philos[0].data->dead_lock);
			return (1);
		}
	else if (philos[philos[0].num_of_philos - 2].meals_eaten == philos[0].num_times_to_eat)
	{
			pthread_mutex_lock(&philos[0].data->dead_lock);
			philos[0].data->is_dead = true;
			pthread_mutex_unlock(&philos[0].data->dead_lock);
			return (1);	
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
			pthread_mutex_lock(&philos[0].data->dead_lock);
			philos[0].data->is_dead = true;
			pthread_mutex_unlock(&philos[0].data->dead_lock);
			printf("%zu %d died\n", get_time(), philos[i].id);
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
	while (1)
		if (dead_loop(philos) == 1 || check_count_eat(philos) == 1)
			break ;
	return (NULL);
}