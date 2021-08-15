/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_semaphore.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 10:52:24 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/04 14:54:12 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		zero_semaphore(t_sem *semaphore)
{
	semaphore->eat_true = 0;
	semaphore->stop_true = 0;
	semaphore->mes_true = 0;
	semaphore->forks_true = 0;
	semaphore->waiter_true = 0;
}

static int		get_num_semaphore(t_sem *sem, int num)
{
	if (!(sem->forks = sem_open("FORKS3", O_CREAT, S_IRWXU, num)))
		return (free_semaphore(sem));
	sem->forks_true++;
	if (!(sem->message = sem_open("PRINT3", O_CREAT, S_IRWXU, 1)))
		return (free_semaphore(sem));
	sem->mes_true++;
	if (!(sem->eat = sem_open("EAT3", O_CREAT, S_IRWXU, 0)))
		return (free_semaphore(sem));
	sem->eat_true++;
	if (!(sem->stop = sem_open("STOP3", O_CREAT, S_IRWXU, 0)))
		return (free_semaphore(sem));
	sem->stop_true++;
	if (!(sem->waiter = sem_open("WAITER3", O_CREAT, S_IRWXU, 1)))
		return (free_semaphore(sem));
	sem->waiter_true++;
	return (0);
}

static void		unlink_sem(void)
{
	sem_unlink("FORKS3");
	sem_unlink("PRINT3");
	sem_unlink("EAT3");
	sem_unlink("STOP3");
	sem_unlink("WAITER3");
}

int				get_sem(t_sem *semaphore, t_data *data, int num)
{
	zero_semaphore(semaphore);
	unlink_sem();
	if (get_num_semaphore(semaphore, num))
		return (1);
	data->stop = semaphore->stop;
	data->eat = semaphore->eat;
	data->print = semaphore->message;
	data->fork = semaphore->forks;
	data->waiter = semaphore->waiter;
	data->ret = 0;
	return (0);
}
