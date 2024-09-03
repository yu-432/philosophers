/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:11:00 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/03 12:35:33 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork) != 0)
		return (write(2, "Error:Mutex lock\n", 17), -1);
	print_msg(philo, "has taken a fork");
	if (pthread_mutex_lock(philo->l_fork) != 0)
		return (write(2, "Error:Mutex lock\n", 17), -1);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->last_meal = get_time();
	usleep(philo->time_to_eat * 1000);
	if (pthread_mutex_unlock(philo->l_fork) != 0)
		return (write(2, "Error:Mutex unlock\n", 19), -1);
	if (pthread_mutex_unlock(philo->r_fork) != 0)
		return (write(2, "Error:Mutex unlock\n", 19), -1);
	philo->meals_eaten++;
	return (0);
}

void	think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

void	ft_sleep(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}