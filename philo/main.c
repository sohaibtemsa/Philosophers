/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:39:12 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/06 14:33:48 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	go(t_data *data)
{
	int		cnt;
	t_philo	*philo;

	cnt = -1;
	philo = data->philo;
	data->start_time = ft_gettime();
	while (++cnt < data->nb_of_philo)
	{
		philo[cnt].last_eat = ft_gettime();
		if ((pthread_create(&(philo[cnt].thread_nb),
					NULL, fun_first, &philo[cnt]) != 0))
			return (0);
		pthread_detach(data->philo[cnt].thread_nb);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		cnt;

	cnt = -1;
	if (ac != 5 && ac != 6)
		return (0);
	if (pars(ac, av))
		return (0);
	data = malloc(sizeof(t_data));
	if (!(data))
		return (0);
	init_data(data, av);
	if (init_philo(data) == 0 || init_mutex(data) == 0)
		return (0);
	data->check = 0;
	if (!go(data))
		return (0);
	all_eat_or_die(data);
	if (data->is_dead == 1)
		return (0);
	destroy_all(data);
}
