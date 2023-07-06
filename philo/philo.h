/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stemsama <stemsama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:39:30 by stemsama          #+#    #+#             */
/*   Updated: 2023/07/06 14:34:03 by stemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eat_fr_each;
	long long		start_time;
	int				all_eat;
	int				is_dead;
	int				check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	for_check;
	pthread_mutex_t	dead;
	pthread_mutex_t	for_dead;
	pthread_mutex_t	l_eat;
	pthread_mutex_t	for_all_eat;
	pthread_mutex_t	for_nb_of_eat;
	struct s_philo	*philo;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			l_f;
	int			r_f;
	int			nb_of_eat;
	long long	last_eat;
	pthread_t	thread_nb;
	t_data		*data;
}	t_philo;

//-----------------------------------------------------------> Parsing.c
int			check_eat(t_data *data);
int			for_norm(t_data *data, int i);
void		all_eat_or_die(t_data *data);
int			for_norm2(t_data *data);
void		*fun_first(void *philoo);

//-----------------------------------------------------------> tools1.c
long long	ft_gettime(void);
void		mute_write(t_data *data, char *str, int nb_philo);
void		init_data(t_data *data, char **av);
int			init_philo(t_data *data);
int			init_mutex(t_data *data);

//-----------------------------------------------------------> tools2.c
void		affiche_er(void);
int			ft_atoi(char *str);
void		eat(t_philo *philo);
void		ft_sleep(int t);

//-----------------------------------------------------------> tools3.c
void		destroy_all(t_data *data);
int			pars(int ac, char **av);

#endif