/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:56:40 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/02 19:42:46 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <limits.h>

void print_msg(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (check_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	printf("%0.10zu %d %s\n", get_time() - philo->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

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

	if (gettimeofday(&tv, NULL) != 0)
	{
		write(2, "Error:Gettimeofday failed\n", 26);
		return (0);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}