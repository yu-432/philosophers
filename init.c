/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:13:14 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/31 11:44:48 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_init(int philo_cnt, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < philo_cnt)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (0);
}

void	input_init(int argc, char **argv, t_philo *philo)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

int	philo_init(int argc, char **argv, t_philo *philo, pthread_mutex_t *fork)
{
	int	i;
	int	p_cnt;

	i = 0;
	p_cnt = ft_atoi(argv[1]);
	while (i < p_cnt)
	{
		input_init(argc, argv, &philo[i]);
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].last_meal = get_time();
		philo[i].start_time = get_time();
		philo[i].dead = false;
		philo[i].write_lock = false;
		philo[i].dead_lock = false;
		philo[i].meal_lock = false;
		philo[i].l_fork = &fork[i];
		if (i == 0)
			philo[i].r_fork = &fork[philo[i].num_of_philos - 1];
		else
			philo[i].r_fork = &fork[i - 1];
		i++;
	}
	return (0);
}
