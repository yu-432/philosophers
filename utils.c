/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:56:40 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/09 11:32:48 by yooshima         ###   ########.fr       */
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

void	ft_usleep(size_t time)
{
	size_t	start;

	start = get_time();
	while (1)
	{
		if (get_time() - start >= time)
			break ;
		usleep(10);
	}
}

void	print_log(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->is_dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_lock(philo->output_lock);
	printf("%zu %d %s\n", get_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(philo->output_lock);
	pthread_mutex_unlock(philo->dead_lock);
}
