/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:34:59 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 09:47:33 by cmalt            ###   ########.fr       */
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

static void		philo_pars(t_philo *philo, t_data *data, t_mutex *mutex, int i)
{
	philo->num = i;
	philo->data = data;
	philo->left = &mutex->forks[i - 1];
	philo->right = (i == data->num) ? &mutex->forks[0] : &mutex->forks[i];
	philo->eat = &mutex->eat[i - 1];
	philo_pars_2(philo);
}

int				init_philo(t_data *data, t_philo **philo, t_mutex *mutex)
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
		philo_pars(new, data, mutex, i);
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
