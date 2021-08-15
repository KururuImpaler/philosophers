/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:34:59 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 11:29:11 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		philo_pars_2(t_philo *philo)
{
	philo->stop = 1;
	philo->count = 0;
	philo->st_eat = 0;
	philo->end = 2000000000000000000;
	philo->start = 0;
	philo->next = NULL;
	philo->prev = NULL;
	philo->t_death = 0;
}

static void		philo_pars(t_philo *philo, t_data *data, t_sem *sem, int i)
{
	philo->num = i;
	philo->data = data;
	philo->fork = sem->forks;
	philo->eat = sem->eat;
	philo_pars_2(philo);
}

int				init_philo(t_data *data, t_philo **philo, t_sem *semaphore)
{
	t_philo	*new;
	t_philo	*tmp;
	int		i;

	i = 0;
	while (i++ < data->num)
	{
		if (!(new = malloc(sizeof(t_philo))))
			return (free_philo(*philo, NULL));
		if (!(new->s = malloc(33)))
			return (free_philo(*philo, new));
		if (!(new->death = malloc(33)))
			return (free_philo(*philo, new));
		philo_pars(new, data, semaphore, i);
		if (!(*philo) && (*philo = new))
			continue ;
		tmp = *philo;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (0);
}
