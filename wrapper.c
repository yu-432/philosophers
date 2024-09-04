/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:23:16 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/04 12:40:54 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_func(pthread_mutex_t *mutex, t_philo *philo, int op)
{
	if (op == INIT)
		if (pthread_mutex_init(mutex, NULL) != 0)
		{
			philo->data->is_error = true;
			write(2, "Erorr:Mutex init failed\n", 24);
		}
	if (op == LOCK)
		if (pthread_mutex_lock(mutex) != 0)
		{
			philo->data->is_error = true;
			write(2, "Erorr:Mutex lock failed\n", 24);
		}
	if (op == UNLOCK)
		if (pthread_mutex_unlock(mutex) != 0)
		{
			philo->data->is_error = true;
			write(2, "Erorr:Mutex unlock failed\n", 26);
		}
	if (op == DESTROY)
		if (pthread_mutex_destroy(mutex) != 0)
		{
			philo->data->is_error = true;
			write(2, "Erorr:Mutex destroy failed\n", 27);
		}
}

void print_msg(t_philo *philo, char *str)
{
	if (check_dead(philo))
		return ;
	printf("%0.10zu %d %s\n", get_time() - philo->start_time, philo->id, str);
}