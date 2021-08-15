/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_monitors_pthreads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:39:54 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 11:34:10 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		create_pthread(t_philo *philo)
{
	int		i;
	t_data	*data;

	i = 0;
	data = philo->data;
	if (pthread_create(&philo->p_stop, NULL, stop, (void *)philo) || ++i == 0)
		return (i);
	if (pthread_create(&philo->p_death, NULL, death, (void *)philo) || ++i == 0)
		return (i);
	philo->start = get_times(data->zero);
	if (data->num == philo->num && philo->num % 2)
		skip_time(philo, philo->start + data->t_eat + data->t_sleep / 2);
	else if (philo->num > data->num / 2)
		skip_time(philo, philo->start + data->t_eat);
	philo->end = philo->start + data->t_live;
	return (i);
}

void	*fatal_philo(t_philo *philo, int i)
{
	t_data	*data;
	int		j;

	data = philo->data;
	sem_wait(data->print);
	j = 0;
	while (j++ < data->num)
		sem_post(data->stop);
	sem_post(philo->eat);
	philo->stop = 0;
	data->ret = 1;
	skip_time(philo, get_times(data->zero) + (data->num * 10));
	sem_post(data->print);
	if (i > 0)
		pthread_join(philo->p_stop, NULL);
	return (NULL);
}
