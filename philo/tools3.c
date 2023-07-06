/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:04:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/06 14:34:06 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->l_eat);
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->for_check);
}

int	pars(int ac, char **av)
{
	int	i;

	(void) ac;
	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) == 0)
			return (1);
	}
	return (0);
}
