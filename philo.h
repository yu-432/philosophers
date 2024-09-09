/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:10:17 by yooshima          #+#    #+#             */
/*   Updated: 2024/09/09 13:06:27 by yooshima         ###   ########.fr       */
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

# define PHILO_MAX 500

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
	bool			*is_dead;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*output_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_lock
{
	bool			is_dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	output_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}	t_lock;

//main
void	destroy_all(t_philo *philos, pthread_mutex_t *fork);

//thread
bool	thread_make(t_philo *philo);

//action
bool	eat(t_philo *philo);
void	sleeping(t_philo *philo);
void	think(t_philo *philo);

//init
bool	philo_init(char **argv, t_lock *lock_data, t_philo *philos, \
					pthread_mutex_t *fork);
bool	fork_init(int fork_cnt, pthread_mutex_t *fork);
bool	lock_init(t_lock *lock_data, t_philo *philos);

//utils
int		ft_atoi(char *s);
void	ft_usleep(size_t time);
size_t	get_time(void);
void	print_log(t_philo *philo, char *str);

//watcher
void	*w_routine(void *pointer);
bool	is_dead(t_philo *philo);

#endif
