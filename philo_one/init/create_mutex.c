/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:34:19 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 09:48:19 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		zero_mutex(t_mutex *mutex)
{
	mutex->eat_true = 0;
	mutex->stop_true = 0;
	mutex->mes_true = 0;
	mutex->forks_true = 0;
}

static int		get_num_mutex(t_mutex *mutex, int num)
{
	int		i;

	if (!(mutex->forks = malloc(sizeof(pthread_mutex_t) * num)))
		return (1);
	if (!(mutex->eat = malloc(sizeof(pthread_mutex_t) * num)))
		return (free_mutex(mutex));
	i = 0;
	while (i < num)
	{
		if (pthread_mutex_init(&(mutex->forks[i]), NULL))
			return (free_mutex(mutex));
		mutex->forks_true++;
		if (pthread_mutex_init(&(mutex->eat[i]), NULL))
			return (free_mutex(mutex));
		pthread_mutex_lock(&mutex->eat[i]);
		mutex->eat_true++;
		i++;
	}
	return (0);
}

static int		get_one_mutex(t_mutex *mutex)
{
	if (pthread_mutex_init(&(mutex->stop), NULL))
		return (free_mutex(mutex));
	pthread_mutex_lock(&mutex->stop);
	mutex->stop_true++;
	if (pthread_mutex_init(&(mutex->message), NULL))
		return (free_mutex(mutex));
	mutex->mes_true++;
	return (0);
}

int				get_mutex(t_mutex *mutex, t_data *data, int num)
{
	zero_mutex(mutex);
	if (get_num_mutex(mutex, num))
		return (1);
	if (get_one_mutex(mutex))
		return (1);
	data->stop = &mutex->stop;
	data->eat = mutex->eat;
	data->print = &mutex->message;
	data->fork = mutex->forks;
	data->ret = 0;
	return (0);
}
