/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:08:52 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/07 13:48:43 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_arg(int argc, char **argv)
{
	int	i;
	int	res;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		res = ft_atoi(argv[i]);
		if (res <= 0 || (i == 1 && res > PHILO_MAX))
			return (false);
		i++;
	}
	return (true);
}

bool	philo_fork_make(t_philo **philo, pthread_mutex_t **fork, int num)
{
	*philo = (t_philo *)malloc(sizeof(t_philo) * num);
	if (!*philo)
	{
		write(2, "Error:Philo malloc failed\n", 26);
		return (false);
	}
	*fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num);
	if (!*fork)
	{
		write(2, "Error:Fork malloc failed\n", 25);
		free(*philo);
		return (false);
	}
	return (true);
}

void	destroy_all(t_philo *philos, pthread_mutex_t *fork, int philo_cnt)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
	i = 0;
	while (i < philo_cnt)
	{
		pthread_mutex_destroy(&philos[i].write_lock);
		i++;
	}
	free(philos);
	free(fork);
	return ;
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	pthread_mutex_t	*fork;
	t_data			data;

	if (!check_arg(argc, argv))
		return (write(2, "Error:Invalid args. 3 700 200 200 [10]\n", 39), 1);
	if (!philo_fork_make(&philos, &fork, ft_atoi(argv[1])))
		return (1);
	if (!fork_init(ft_atoi(argv[1]), fork) || !data_init(&data))
		return (1);
	if (!philo_init(argv, &data, philos, fork))
		return (1);
	if (!thread_make(philos))
		return (destroy_all(philos, fork, philos[0].num_of_philos), 1);
	destroy_all(philos, fork, philos[0].num_of_philos);
	return (0);
}
