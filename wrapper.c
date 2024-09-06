/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:23:16 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/06 18:35:51 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_func(pthread_mutex_t *mutex, t_philo *philo, int op)
{
	if (op == LOCK && !philo->data->is_dead)
	{
		if (pthread_mutex_lock(mutex) != 0)
		{
			philo->data->is_dead = true;
			write(2, "Error:Mutex lock failed\n", 24);
		}
	}
	else if (op == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
		{
			philo->data->is_dead = true;
			write(2, "Error:Mutex unlock failed\n", 26);
		}
	}
}
