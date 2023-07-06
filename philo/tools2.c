/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:39:44 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/06 14:34:05 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	affiche_er(void)
{
	write(2, "Error\n", 6);
}

int	ft_atoi(char *str)
{
	long long	n;
	int			i;

	n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (str[i] || n > 2147483647)
		return (0);
	return (n);
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->forks[philo->l_f]));
	mute_write(data, "has taken a left fork", philo->id + 1);
	pthread_mutex_lock(&(data->forks[philo->r_f]));
	mute_write(data, "has taken a right fork", philo->id + 1);
	mute_write(data, "is eating", philo->id + 1);
	pthread_mutex_lock(&data->for_nb_of_eat);
	philo->nb_of_eat++;
	pthread_mutex_unlock(&data->for_nb_of_eat);
	pthread_mutex_lock(&data->l_eat);
	philo->last_eat = ft_gettime();
	pthread_mutex_unlock(&data->l_eat);
	ft_sleep(data->time_to_eat);
	pthread_mutex_unlock(&(data->forks[philo->l_f]));
	pthread_mutex_unlock(&(data->forks[philo->r_f]));
}

void	ft_sleep(int t)
{
	long long	time;

	time = ft_gettime();
	while (!(ft_gettime() - time >= t))
		usleep(500);
}
