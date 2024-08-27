/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:10:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/27 12:45:24 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <string.h>

# define PHILO_MAX 250
//test
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	size_t			last_meal;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
}	t_philo;

void	philo_init(argc, argv, &philo);
int		only_nb_atoi(char *s);
size_t	get_time(void);
int	fork_init(pthread_mutex_t *fork);
void destroy_all(int f_cnt, int m_cnt, pthread_mutex_t *fork, t_philo *philo);


#endif