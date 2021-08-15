/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pthreads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:35:58 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/03 10:52:28 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		wait_philo(int i, pid_t *pid, t_data *data, int n)
{
	int		stat;

	if (n == 0)
		sem_post(data->stop);
	if (n < 2 && data->args == 6 && i > data->num)
	{
		waitpid(pid[--i], &stat, 0);
		if (WEXITSTATUS(stat))
			n = 0;
	}
	while (n < 2 && i-- > 0)
	{
		waitpid(pid[i], &stat, 0);
		if (WEXITSTATUS(stat))
			n = 0;
	}
	if (pid)
		free(pid);
	return (n);
}

int		create_philo(int (*func)(void *), void *arg, pid_t *pid, int i)
{
	pid[i] = fork();
	if (pid[i] < 0)
		return (0);
	if (pid[i] == 0)
		return (func(arg));
	return (1);
}

void	init(t_data *data, t_philo **philo)
{
	pid_t		*pid;
	int			i;
	t_philo		*tmp;
	int			n;

	n = 1;
	if (!(pid = malloc(sizeof(pid_t) * (data->num + 1))))
		n = 0;
	i = -1;
	tmp = *philo;
	while (++i < data->num && n == 1)
	{
		n = create_philo(&philo_three, (void *)tmp, pid, i);
		tmp = tmp->next;
	}
	if (n == 1 && data->args == 6 && ++i)
		n = create_philo(&limit_eat, (void *)data, pid, data->num);
	n = wait_philo(i, pid, data, n);
	data->ret = (n == 0 || n == 2) ? n + 1 : data->ret;
}
