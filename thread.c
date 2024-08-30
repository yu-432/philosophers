/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/29 12:37:21 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	if (philo->dead == true)
		return (1);
	return (0);
}

void *p_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!dead_check(philo))
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

	pthread_create(&watcher, NULL, w_routine, &philo);
	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, p_routine, &philo[i]) != 0)
			return (write(2, "Error:Thread create\n", 20), -1);
		i++;
	}
	pthread_join(watcher, NULL);
	i = 0;
	while (i < philo[0].num_of_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (0);
}

void	destroy_all(t_philo *philo, pthread_mutex_t *fork)
{
	int i;

	i = -1;
	while (i++ < philo[0].num_of_philos)
		pthread_mutex_destroy(&fork[i - 1]);
	return ;
}
