/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:11:00 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/06 21:33:18 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
		return (ft_usleep(philo->time_to_sleep, philo), false);
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	philo->last_meal = get_time();
	ft_usleep(philo->time_to_eat, philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	philo->meals_eaten++;
	return (true);
}

void	think(t_philo *philo)
{
	print_log(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep, philo);
}
