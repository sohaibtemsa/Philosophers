/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:39:24 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/06 14:34:01 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->for_nb_of_eat);
	while (i < data->nb_of_philo
		&& data->philo[i].nb_of_eat >= data->nb_of_eat_fr_each)
	{
		i++;
	}
	if (i == data->nb_of_philo)
	{
		pthread_mutex_lock(&data->for_all_eat);
		data->all_eat = 1;
		pthread_mutex_unlock(&data->for_all_eat);
		pthread_mutex_unlock(&data->for_nb_of_eat);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->for_nb_of_eat);
	return (0);
}

int	for_norm(t_data *data, int i)
{
	pthread_mutex_lock(&data->l_eat);
	if (ft_gettime() - data->philo[i].last_eat >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->l_eat);
		pthread_mutex_lock(&data->for_dead);
		data->is_dead = 1;
		pthread_mutex_unlock(&data->for_dead);
		pthread_mutex_lock(&data->write);
		printf("%lld %d died\n",
			ft_gettime() - data->start_time, data->nb_of_philo);
		pthread_mutex_unlock(&data->write);
		pthread_mutex_lock(&data->for_check);
		data->check = 1;
		pthread_mutex_unlock(&data->for_check);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->l_eat);
	return (0);
}

void	all_eat_or_die(t_data *data)
{
	int	i;

	while (!data->all_eat)
	{
		i = -1;
		while (++i < data->nb_of_philo && !data->is_dead)
		{
			if (for_norm(data, i) == 1)
				return ;
		}
		if (data->nb_of_eat_fr_each != 0)
		{
			if (check_eat(data))
				return ;
		}
	}
	return ;
}

int	for_norm2(t_data *data)
{
	pthread_mutex_lock(&data->for_dead);
	pthread_mutex_lock(&data->for_all_eat);
	if (data->all_eat || data->is_dead)
	{
		pthread_mutex_unlock(&data->for_all_eat);
		pthread_mutex_unlock(&data->for_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->for_all_eat);
	pthread_mutex_unlock(&data->for_dead);
	return (0);
}

void	*fun_first(void *philoo)
{
	t_philo	*philo;
	t_data	*data;
	int		is_dead;

	philo = (t_philo *)philoo;
	data = philo->data;
	pthread_mutex_lock(&data->for_dead);
	is_dead = data->is_dead;
	pthread_mutex_unlock(&data->for_dead);
	if (philo->id % 2 != 0)
		usleep(500);
	while (!is_dead)
	{
		eat(philo);
		if (for_norm2(data) == 1)
			return (NULL);
		mute_write(data, "is sleeping", philo->id + 1);
		ft_sleep(data->time_to_sleep);
		mute_write(data, "is thinking", philo->id + 1);
	}
	return (NULL);
}
