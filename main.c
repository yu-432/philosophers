/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:08:52 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/27 12:06:20 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) == -1 \
			|| (i == 1 && ft_atoi(argv[i]) > PHILO_MAX))
			return (-1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	fork[PHILO_MAX];

	if ((argc != 5 && argc != 6) || check_arg(argc, argv) == -1)
		return (write(2, "Error:Invalid args. 3 700 200 200 [10]\n", 39), 1);
	if (fork_init(ft_atoi(argv[1]), fork) == -1 \
		|| philo_init(argc, argv, philo, fork) == -1)
		return (1);
	thread_make(philo, fork);
	return (0);
}
