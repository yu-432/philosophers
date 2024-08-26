/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:56:40 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/26 15:59:42 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	only_nb_atoi(char *s)
{
	long	nbs;

	nbs = 0;
	while (*s)
	{
		if (*s > '0' || '9' < *s)
			return (-1);
		nbs = nbs * 10 + (*s - '0');
		s++;
	}
	return (nbs);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		write(2, "Error:Gettimeofday error\n", 25);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}