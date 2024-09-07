/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:13:14 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/07 14:19:53 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	fork_init(int philo_cnt, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < philo_cnt)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			write(2, "Error:Fork mutex init failed\n", 29);
			while (i > 0)
			{
				pthread_mutex_destroy(&fork[i - 1]);
				i--;
			}
			return (false);
		}
		i++;
	}
	return (true);
}

bool	data_init(t_data *data)
{
	data->is_dead = false;
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->output_lock, NULL) != 0)
		return (false);
	return (true);
}

void	input_init(char **argv, t_philo *philo)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

bool	philo_init(char **argv, t_data *data, t_philo *philos, \
	pthread_mutex_t *fork)
{
	int	i;
	int	p_cnt;

	i = 0;
	p_cnt = ft_atoi(argv[1]);
	while (i < p_cnt)
	{
		input_init(argv, &philos[i]);
		if (pthread_mutex_init(&philos[i].write_lock, NULL))
			return (destroy_all(philos, fork, i), false);
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
		philos[i].data = data;
		philos[i].l_fork = &fork[i];
		if (i == 0)
			philos[i].r_fork = &fork[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &fork[i - 1];
		i++;
	}
	return (true);
}
