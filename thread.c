/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:04:31 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/27 12:35:32 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_philo *philo)
{
	if (*philo->dead == 1)
		return (1);
	return (0);
}

void *routine(void *pointer)
{
	t_philo *philo;
	
	philo = (t_philo *)pointer;
	if (philo->id & 2 == 0)
		usleep(10);
	while ()
}

int	thread_make(t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i++ < philo[0].num_of_philo)
	{
		
	}
}
