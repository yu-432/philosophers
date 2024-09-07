/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:11:00 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/07 15:10:43 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_log(philo, "has taken a fork");
	if (philo->num_of_philos == 1)
		return (ft_usleep(philo->time_to_die), false);
	pthread_mutex_lock(philo->l_fork);
	print_log(philo, "has taken a fork");
	print_log(philo, "is eating");
	pthread_mutex_lock(&philo->write_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->write_lock);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(&philo->write_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->write_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (true);
}

void	think(t_philo *philo)
{
	print_log(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	print_log(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}
