/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:11:00 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/27 14:24:25 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (write(2, "Error:Mutex lock\n", 17), -1);
	printf("%u %d has taken a fork\n", get_time(), philo->id);
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (write(2, "Error:Mutex lock\n", 17), -1);
	printf("%u %d has taken a fork\n", get_time(), philo->id);
	philo->eating = 1;
	printf("%u %d is eating\n", get_time(), philo->id);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	usleep(philo->time_to_eat);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (write(2, "Error:Mutex unlock\n", 19), -1);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (write(2, "Error:Mutex unlock\n", 19), -1);
	return (0);
}

void	think(t_philo *philo)
{
	printf("%u %d is thinking\n", get_time(), philo->id);
}

void	sleep(t_philo *philo)
{
	printf("%u %d is sleeping\n", get_time(), philo->id);
	usleep(philo->time_to_sleep);
}