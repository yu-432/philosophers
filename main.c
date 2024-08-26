/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yooshima <yooshima@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:08:52 by yooshima          #+#    #+#             */
/*   Updated: 2024/08/26 14:33:31 by yooshima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (only_nb_atoi(argv[i]) == -1)
			return (-1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if ((argc != 5 && argc != 6) || check_arg(argc, argv) == -1)
		return (printf("Invalid args. Sample ./philo 3 700 200 200 [10]\n"), 1);
	philo_init(&philo, argv);
}
