/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:13:14 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/27 11:56:41 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_init(int fork_cnt, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i++ < fork_cnt)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
		{
			while (i-- >= 0)
				pthread_mutex_destroy(&fork[i]);
			return (write(2, "Error:Fork mutex init\n", 22), -1);
		}
	}
	return (0);
}

void	input_other_init(int argc, char **argv, t_philo *philo)
{
	philo->eating = 0;
	philo->meals_eaten = 0;
	philo->last_meal = get_time();
	philo->start_time = get_time();
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
	while (i++ < p_cnt)
	{
		input_other_init(argc, argv, &philo[i]);
		philo[i].id = i + 1;
		if (pthread_mutex_init(&philo[i].write_lock, NULL) == -1)
			return (clear_mutex(p_cnt, i - 1, fork, philo), -1);
		if (pthread_mutex_init(&philo[i].dead_lock, NULL) == -1)
			return (pthread_mutex_destroy(&philo[i].write_lock), \
				clear_mutex(p_cnt, i - 1, fork, philo), -1);
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) == -1)
			return (pthread_mutex_destroy(&philo[i].write_lock), \
				pthread_mutex_destroy(&philo[i].dead_lock), \
				clear_mutex(p_cnt, i - 1, fork, philo), -1);
		philo[i].l_fork = fork[i];
		if (i == 0)
			philo[i].r_fork = fork[ft_atoi(argv[1]) - 1];
		else
			philo[i].r_fork = fork[i - 1];
	}
	return (0);
}

//確保したフォーク、ふぃろのmutexを全て破壊する、しろ
void	clear_mutex(int f_cnt, int p_cnt, pthread_mutex_t *fork, t_philo *philo)
{
	int	i;
	int	j;

	i = 0;
	while (i++ < f_cnt)
		pthread_mutex_destroy(&fork[i]);
	j = 0;
	while (j++ < p_cnt)
	{
		pthread_mutex_destroy(&philo[j].write_lock);
		pthread_mutex_destroy(&philo[j].dead_lock);
		pthread_mutex_destroy(&philo[j].meal_lock);
	}
}
