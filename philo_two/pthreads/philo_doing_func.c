/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_doing_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:40:31 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/04 05:25:50 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take(t_philo *philo)
{
	sem_wait(philo->data->waiter);
	sem_wait(philo->fork);
	print(philo, 1);
	sem_wait(philo->fork);
	sem_post(philo->data->waiter);
	philo->to_next = get_times(philo->data->zero);
	print(philo, 1);
	philo->st_eat = 1;
	philo->end = philo->to_next + philo->data->t_live;
}

void	philo_eat(t_philo *philo)
{
	print(philo, 2);
	philo->count++;
	philo->to_next = philo->to_next + philo->data->t_eat;
	skip_time(philo, philo->to_next);
	sem_post(philo->fork);
	sem_post(philo->fork);
	philo->st_eat = 0;
}

void	philo_sleep(t_philo *philo)
{
	print(philo, 3);
	philo->to_next = philo->to_next + philo->data->t_sleep;
	skip_time(philo, philo->to_next);
}

void	philo_think(t_philo *philo)
{
	print(philo, 4);
}
