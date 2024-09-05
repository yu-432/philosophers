/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/05 14:48:42 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->num_of_philos % 2 == 0 && philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat, philo);
	else if (philo->num_of_philos % 2 == 1)
	{
		if (philo->id % 2 == 0)
			ft_usleep((philo->time_to_eat / philo->num_of_philos) * \
					(philo->id - 2) + philo->time_to_eat, philo);
		else
			ft_usleep((philo->time_to_eat / philo->num_of_philos) * \
					(philo->id - 1), philo);
	}
	while (!philo->data->is_dead)
	{
		if (!eat(philo))
			break ;
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

bool	thread_make(t_philo *philo, pthread_mutex_t *fork)
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
	while (++i < philo[0].num_of_philos)
		pthread_detach(philo[i].thread);
	pthread_join(watcher, &res);
	//	pthread_join(philo[i].thread, NULL);
	return (true);
}
