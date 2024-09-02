/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/02 14:40:35 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->is_dead == true)
		return (pthread_mutex_unlock(&philo->data->dead_lock), 1);
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

void *p_routine(void *pointer)
{
	t_philo *philo;

	philo = (t_philo *)pointer;
	if (philo->num_of_philos % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(philo->time_to_eat * 500);
	}
	else
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
	while (i < philo[0].num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, p_routine, &philo[i]) != 0)
			return (write(2, "Error:Thread create\n", 20), -1);
		i++;
	}
	pthread_create(&watcher, NULL, w_routine, philo);
	i = 0;
	while (i < philo[0].num_of_philos)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(watcher, NULL);
	return (0);
}

void	destroy_all(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		pthread_mutex_destroy(&fork[i - 1]);
		i++;
	}
	return ;
}
