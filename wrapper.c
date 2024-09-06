/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:23:16 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/06 16:29:31 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_func(pthread_mutex_t *mutex, t_philo *philo, int op)
{
	if (philo->data->is_dead)
		return ;
	if (op == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
		{
			philo->data->is_dead = true;
			write(2, "Erorr:Mutex lock failed\n", 24);
		}
	}
	else if (op == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0)
		{
			philo->data->is_dead = true;
			write(2, "Erorr:Mutex unlock failed\n", 26);
		}
	}
}

void	print_log(t_philo *philo, char *str)
{
	mutex_func(&philo->data->write_lock, philo, LOCK);
	printf("%0.10zu %d %s\n", get_time() - philo->start_time, philo->id, str);
	mutex_func(&philo->data->write_lock, philo, UNLOCK);
}
