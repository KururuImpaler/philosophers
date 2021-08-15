/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthreads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:35:58 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/04 05:24:53 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_philo(int i, pthread_t *pid, t_data *data, int n)
{
	if (n == 0)
		pthread_mutex_unlock(data->stop);
	if (data->args == 6 && i > data->num)
		pthread_join(pid[--i], NULL);
	while (i-- > 0)
		pthread_join(pid[i], NULL);
	if (pid)
		free(pid);
}

int		create_philo(void *(*func)(void *), void *arg, pthread_t *pid, int i)
{
	if (pthread_create(&pid[i], NULL, func, arg))
		return (0);
	return (1);
}

void	init(t_data *data, t_philo **philo)
{
	pthread_t	*pid;
	int			i;
	t_philo		*tmp;
	int			n;

	n = 1;
	if (!(pid = malloc(sizeof(pthread_t) * (data->num + 1))))
		n = 0;
	i = -1;
	tmp = *philo;
	while (++i < data->num && n)
	{
		n = create_philo(&philo_one, (void *)tmp, pid, i);
		tmp = tmp->next;
	}
	if (n && data->args == 6 && ++i)
		n = create_philo(&limit_eat, (void *)data, pid, data->num);
	wait_philo(i, pid, data, n);
	data->ret = (n == 0) ? 1 : data->ret;
}
