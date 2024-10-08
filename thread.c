/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/08 21:14:45 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->num_of_philos % 2 == 0 && philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat);
	else if (philo->num_of_philos % 2 == 1)
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo->time_to_eat * (philo->id - 1) \
					/ philo->num_of_philos + philo->time_to_eat);
		else
			ft_usleep(philo->time_to_eat * (philo->id - 1) \
					/ philo->num_of_philos);
	}
	while (!is_dead(philo))
	{
		if (!eat(philo))
			break ;
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

bool	thread_make(t_philo *philo)
{
	int			i;
	void		*res;
	pthread_t	watcher;

	i = -1;
	while (++i < philo[0].num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, p_routine, \
			&philo[i]) != 0)
		{
			while (--i >= 0)
				pthread_detach(philo[i].thread);
			return (write(2, "Error:Thread create\n", 20), false);
		}
	}
	if (pthread_create(&watcher, NULL, w_routine, philo) != 0)
		return (write(2, "Error:Thread create\n", 20), false);
	i = -1;
	pthread_join(watcher, &res);
	while (++i < philo[0].num_of_philos)
		pthread_join(philo[i].thread, NULL);
	return (true);
}
