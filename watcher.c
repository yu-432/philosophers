/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:07:49 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/28 12:42:31 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_count_eat(t_philo *philos)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (i++ < philos[0].num_of_philos)
		if (philos[i-1].meals_eaten == philos[0].time_to_eat)
			count++;
	if (count == philos[0].num_of_philos)
		return (1);
	return (0);
}

int	check_dead(t_philo *philos)
{
	int	i;

	i = -1;
	while (i++ < philos[0].num_of_philos)
		if (get_time() - philos[i-1].last_meal > philos[i-1].time_to_die)
		{
			philos[i-1].dead = true;
			printf("dead\n");
			return (1);
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
	return (pointer);
}