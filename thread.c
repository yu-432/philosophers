/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/03 13:32:13 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	mutex_func(&philo->data->dead_lock, philo, LOCK);
	if (philo->data->is_dead == true)
		return (mutex_func(&philo->data->dead_lock, philo, UNLOCK), 1);
	mutex_func(&philo->data->dead_lock, philo, UNLOCK);
	return (0);
}

void *p_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->num_of_philos % 2 == 0 && philo->id % 2 == 0)
	{
		usleep(philo->time_to_eat * 500);
	}
	else if (philo->num_of_philos % 2 == 1)
	{
		if (philo->id % 2 == 0)
			usleep((philo->time_to_eat / philo->num_of_philos) * (philo->id - 2) + philo->time_to_eat * 1000);
		else
			usleep((philo->time_to_eat / philo->num_of_philos) * (philo->id - 1) * 1000);
	}
	while (!check_dead(philo))
	{
		eat(philo);
		ft_sleep(philo);
		think(philo);
	}
	return (pointer);
}

int	thread_make(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;
	pthread_t watcher;

	i = 0;
	while (i++ < philo[0].num_of_philos)
	{
		if (pthread_create(&philo[i - 1].thread, NULL, p_routine, &philo[i - 1]) != 0)
		{
			while (--i >= 0)
				pthread_detach(philo[i].thread);
			return (write(2, "Error:Thread create\n", 20), -1);
		}
	}
	if (pthread_create(&watcher, NULL, w_routine, philo) != 0)
		return (write(2, "Error:Thread create\n", 20), -1);
	i = 0;
	while (i++ < philo[0].num_of_philos)
	{
		if (pthread_join(philo[i - 1].thread, NULL) != 0)
			return (write(2, "Error:Thread join\n", 18), -1);
	}
	if (pthread_join(watcher, NULL) != 0)
		return (write(2, "Error:Thread join\n", 18), -1);
	return (0);
}

void	destroy_all(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		mutex_func(&fork[i], philo, DESTROY);
		i++;
	}
	return ;
}
