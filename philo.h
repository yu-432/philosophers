/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:10:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/05 13:10:51 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

# define PHILO_MAX 1000
# define INIT 1
# define LOCK 2
# define UNLOCK 3
# define DESTROY 4
# define CREATE 5
# define JOIN 6
# define DETACH 7

typedef struct s_data
{
	bool			is_error;
	bool			is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				num_of_philos;
	int				num_times_to_eat;
	size_t			last_meal;
	size_t			start_time;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}	t_philo;

//thread
bool	thread_make(t_philo *philo, pthread_mutex_t *fork);

//mutex

//action
bool	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	think(t_philo *philo);

//init
void	philo_init(char **argv, t_data *data, t_philo *philo, \
					pthread_mutex_t *fork);
bool	fork_init(int fork_cnt, pthread_mutex_t *fork);
bool	data_init(t_data *data);

//utils
int		ft_atoi(char *s);
size_t	get_time(void);
void	print_msg(t_philo *philo, char *str);

void	clear_mutex(int f_cnt, int m_cnt, pthread_mutex_t *fork, \
					t_philo *philo);
void	destroy_all(t_philo *philo, pthread_mutex_t *fork);
void	*w_routine(void *pointer);
bool	is_dead(t_philo *philo);
void	mutex_func(pthread_mutex_t *mutex, t_philo *philo, int op);
void	ft_usleep(int time, t_philo *philo);
bool	philo_make(t_philo **philo, pthread_mutex_t **fork, int num);

#endif