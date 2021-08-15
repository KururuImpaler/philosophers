/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:35:28 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/04 14:54:48 by cmalt            ###   ########.fr       */
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

int		free_semaphore(t_sem *semaphore)
{
	if (semaphore->forks_true > 0)
		sem_close(semaphore->forks);
	sem_unlink("FORKS3");
	if (semaphore->eat_true > 0)
		sem_close(semaphore->eat);
	sem_unlink("EAT3");
	if (semaphore->mes_true > 0)
		sem_close(semaphore->message);
	sem_unlink("PRINT3");
	if (semaphore->stop_true > 0)
		sem_close(semaphore->stop);
	sem_unlink("STOP3");
	if (semaphore->waiter_true > 0)
		sem_close(semaphore->waiter);
	sem_unlink("WAITER3");
	return (1);
}
