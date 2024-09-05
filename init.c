/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:13:14 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/05 13:10:00 by yooshima         ###   ########.fr       */
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

void	philo_init(char **argv, t_data *data, t_philo *philo, \
	pthread_mutex_t *fork)
{
	int	i;
	int	p_cnt;

	i = 0;
	p_cnt = ft_atoi(argv[1]);
	while (i < p_cnt)
	{
		input_init(argv, &philo[i]);
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_time();
		philo[i].start_time = get_time();
		philo[i].data = data;
		philo[i].l_fork = &fork[i];
		if (i == 0)
			philo[i].r_fork = &fork[philo[i].num_of_philos - 1];
		else
			philo[i].r_fork = &fork[i - 1];
		i++;
	}
}

bool	data_init(t_data *data)
{
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (false);
	data->is_dead = false;
	data->is_error = false;
	return (true);
}
