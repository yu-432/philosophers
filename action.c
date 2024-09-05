/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:11:00 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/05 15:01:43 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat(t_philo *philo)
{
	// if (pthread_mutex_lock(philo->r_fork) != 0)
	// 	return (write(2, "Error:Mutex lock\n", 17), false);
	mutex_func(philo->r_fork, philo, LOCK);
	print_msg(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
		return (ft_usleep(philo->time_to_sleep, philo), false);
	// if (pthread_mutex_lock(philo->l_fork) != 0)
	// 	return (write(2, "Error:Mutex lock\n", 17), false);
	mutex_func(philo->l_fork, philo, LOCK);
	print_msg(philo, "has taken a fork");
	print_msg(philo, "is eating");
	philo->last_meal = get_time();
	ft_usleep(philo->time_to_eat, philo);
	// if (pthread_mutex_unlock(philo->l_fork) != 0)
	// 	return (write(2, "Error:Mutex unlock\n", 19), false);
	mutex_func(philo->l_fork, philo, UNLOCK);
	// if (pthread_mutex_unlock(philo->r_fork) != 0)
	// 	return (write(2, "Error:Mutex unlock\n", 19), false);
	mutex_func(philo->r_fork, philo, UNLOCK);
	philo->meals_eaten++;
	return (true);
}

void	think(t_philo *philo)
{
	print_msg(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	print_msg(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
}
