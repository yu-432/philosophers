/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:08:52 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/09 13:14:14 by yooshima         ###   ########.fr       */
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

void	destroy_all(t_philo *philos, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
	pthread_mutex_destroy(philos[0].dead_lock);
	pthread_mutex_destroy(philos[0].output_lock);
	pthread_mutex_destroy(philos[0].write_lock);
	free(philos);
	free(fork);
	return ;
}

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	pthread_mutex_t	*fork;
	t_lock			lock_data;

	if (!check_arg(argc, argv))
		return (write(2, "Error:Invalid args. 3 700 200 200 [10]\n", 39), 1);
	if (!philo_fork_make(&philos, &fork, ft_atoi(argv[1])))
		return (1);
	if (!fork_init(ft_atoi(argv[1]), fork) || !lock_init(&lock_data, philos))
		return (1);
	if (!philo_init(argv, &lock_data, philos, fork))
		return (1);
	if (!thread_make(philos))
		return (destroy_all(philos, fork), 1);
	destroy_all(philos, fork);
	return (0);
}
