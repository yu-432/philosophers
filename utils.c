/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:56:40 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/28 13:24:41 by yooshima         ###   ########.fr       */
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

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "Error:Gettimeofday error\n", 25);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}