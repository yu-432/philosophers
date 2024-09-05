/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/05 09:16:23 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void *p_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->num_of_philos % 2 == 0 && philo->id % 2 == 0)
	{
		ft_usleep(philo->time_to_eat, philo);
	}
	else if (philo->num_of_philos % 2 == 1)
	{
		if (philo->id % 2 == 0)
			ft_usleep((philo->time_to_eat / philo->num_of_philos) * (philo->id - 2) + philo->time_to_eat, philo);
		else
			ft_usleep((philo->time_to_eat / philo->num_of_philos) * (philo->id - 1), philo);
	}
	while (!philo->data->is_dead)
	{
		eat(philo);
		sleeping(philo);
		think(philo);
	}
	return (pointer);
}

bool	thread_make(t_philo *philo, pthread_mutex_t *fork)
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
			return (write(2, "Error:Thread create\n", 20), false);
		}
	}
	if (pthread_create(&watcher, NULL, w_routine, philo) != 0)
		return (write(2, "Error:Thread create\n", 20), false);
	i = 0;
	pthread_join(watcher, NULL);
	while (i++ < philo[0].num_of_philos)
		pthread_join(philo[i - 1].thread, NULL);
	return (true);
}


