/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:13:14 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/28 13:53:48 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_init(int fork_cnt, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < fork_cnt)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			while (i-- >= 0)
				pthread_mutex_destroy(&fork[i]);
			return (write(2, "Error:Fork mutex init\n", 22), -1);
		}
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

//pthread mutex initは失敗時を想定していなければならないか
//一旦初期値が定数のもののみインプット初期化関数にいれたが、mutex初期化を別関数にするべきかもしれない
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
		philo[i].l_fork = fork[i];
		if (i == 0)
			philo[i].r_fork = fork[ft_atoi(argv[1]) - 1];
		else
			philo[i].r_fork = fork[i - 1];
		i++;
	}
	return (0);
}
