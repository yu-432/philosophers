/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:56:40 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/06 18:18:42 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <limits.h>

int	ft_atoi(char *s)
{
	long	nbs;

	nbs = 0;
	while (*s)
	{
		if (*s < '0' || '9' < *s || nbs > INT_MAX)
			return (-1);
		nbs = nbs * 10 + (*s - '0');
		s++;
	}
	return ((int)nbs);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int time, t_philo *philo)
{
	size_t	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
			break ;
		usleep(philo->time_to_sleep);
	}
}

void	print_log(t_philo *philo, char *str)
{
	mutex_func(&philo->data->dead_lock, philo, LOCK);
	if (philo->data->is_dead)
	{
		mutex_func(&philo->data->dead_lock, philo, UNLOCK);
		return ;
	}
	mutex_func(&philo->data->dead_lock, philo, UNLOCK);
	mutex_func(&philo->data->write_lock, philo, LOCK);
	printf("%0.10zu %d %s\n", get_time() - philo->start_time, philo->id, str);
	mutex_func(&philo->data->write_lock, philo, UNLOCK);
}
