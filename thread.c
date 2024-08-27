/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/27 14:58:01 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	if (philo->dead_lock == true)
		return (1);
	return (0);
}

void *routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(10);
	while (!dead_check(philo))
	{
		if (eat(philo) != 0)
			return (-1);
		sleep(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_make(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i++ < philo[0].num_of_philos)
	{
		if (pthread_create(&philo[i], NULL, routine, philo[i]) != 0)
			return (write(2, "Error:Thread create\n", 20), -1);
		
	}
}

void	destroy_all(t_philo *philo, pthread_mutex_t *fork)
{

}
