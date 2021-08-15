/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:37:50 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/04 05:20:20 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*stop(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->stop);
	philo->stop = 0;
	sem_post(philo->data->stop);
	return (NULL);
}

void	*death(void *arg)
{
	t_philo		*philo;
	t_data		*data;
	int			check;

	philo = (t_philo *)arg;
	data = philo->data;
	check = 0;
	while (philo->stop)
	{
		philo->t_death = get_times(data->zero);
		if (philo->t_death >= philo->end && !philo->st_eat)
			print_death(philo);
		if (!check && data->args == 6 && philo->count == data->lim_eat)
		{
			sem_post(philo->eat);
			check++;
		}
	}
	if (!check && data->args == 6)
		sem_post(philo->eat);
	return (NULL);
}

void	*philo_two(void *arg)
{
	t_philo		*philo;
	int			i;

	philo = (t_philo *)arg;
	i = 3;
	if ((i = create_pthread(philo)) < 2)
		return (fatal_philo(philo, i));
	while (philo->stop)
	{
		philo_take(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	pthread_join(philo->p_death, NULL);
	pthread_join(philo->p_stop, NULL);
	return (NULL);
}

void	*limit_eat(void *arg)
{
	t_data		*data;
	int			i;

	data = (t_data *)arg;
	i = 0;
	while (i++ < data->num)
		sem_wait(data->eat);
	sem_post(data->stop);
	return (NULL);
}
