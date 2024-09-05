/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:23:16 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/05 09:19:45 by yooshima         ###   ########.fr       */
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
bool	is_dead(t_philo *philo)
{
	mutex_func(&philo->data->dead_lock, philo, LOCK);
	if (philo->data->is_dead == true)
		return (mutex_func(&philo->data->dead_lock, philo, UNLOCK), false);
	mutex_func(&philo->data->dead_lock, philo, UNLOCK);
	return (true);
}

void print_msg(t_philo *philo, char *str)
{
	if (!is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%10zu %d %s\n", get_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);

}