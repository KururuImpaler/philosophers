/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:35:28 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 09:46:04 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		free_philo(t_philo *philo, t_philo *new_philo)
{
	t_philo	*tmp;

	if (new_philo)
	{
		free(new_philo);
		if (new_philo->s)
			free(new_philo->s);
	}
	while (philo)
	{
		if (philo->s)
			free(philo->s);
		if (philo->death)
			free(philo->death);
		tmp = philo;
		philo = philo->next;
		free(tmp);
	}
	return (1);
}

int		free_mutex(t_mutex *mutex)
{
	int		i;

	i = 0;
	while (mutex->forks && i < mutex->forks_true)
		pthread_mutex_destroy(&(mutex->forks[i++]));
	if (mutex->forks)
		free(mutex->forks);
	i = 0;
	while (mutex->eat && i < mutex->eat_true)
		pthread_mutex_destroy(&(mutex->eat[i++]));
	if (mutex->eat)
		free(mutex->eat);
	(mutex->stop_true) ? pthread_mutex_destroy(&(mutex->stop)) : 0;
	(mutex->mes_true) ? pthread_mutex_destroy(&(mutex->message)) : 0;
	return (1);
}
