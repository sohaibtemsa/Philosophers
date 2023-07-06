/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:39:38 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/06 14:34:04 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	mute_write(t_data *data, char *str, int nb_philo)
{
	pthread_mutex_lock(&data->write);
	pthread_mutex_lock(&data->for_check);
	if (data->check == 0)
		printf("%lld %d %s\n", ft_gettime() - data->start_time, nb_philo, str);
	pthread_mutex_unlock(&data->for_check);
	pthread_mutex_unlock(&data->write);
}

void	init_data(t_data *data, char **av)
{
	data->nb_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->all_eat = 0;
	data->is_dead = 0;
	if (av[5])
		data->nb_of_eat_fr_each = ft_atoi(av[5]);
	else
		data->nb_of_eat_fr_each = 0;
}

int	init_philo(t_data *data)
{
	int			nb;

	nb = data->nb_of_philo;
	data->philo = malloc(sizeof(t_philo) * nb);
	if (!data->philo)
		return (0);
	while (--nb >= 0)
	{
		data->philo[nb].id = nb;
		data->philo[nb].nb_of_eat = 0;
		data->philo[nb].l_f = nb;
		data->philo[nb].r_f = (nb + 1) % data->nb_of_philo;
		data->philo[nb].data = data;
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	int	nb;

	nb = data->nb_of_philo;
	data->forks = malloc(sizeof(pthread_mutex_t) * nb);
	while (--nb >= 0)
	{
		if (pthread_mutex_init(&(data->forks[nb]), NULL) != 0)
			return (0);
	}
	if (pthread_mutex_init(&(data->write), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->l_eat), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->for_all_eat), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->for_nb_of_eat), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->dead), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->for_dead), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->for_check), NULL) != 0)
		return (0);
	return (1);
}
