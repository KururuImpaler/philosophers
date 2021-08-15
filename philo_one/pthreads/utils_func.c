/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:41:32 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 09:59:45 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_timer		get_times(struct timeval zero)
{
	t_timer			ret;
	struct timeval	t;

	gettimeofday(&t, NULL);
	ret = (t.tv_sec - zero.tv_sec) * 1000;
	ret += (t.tv_usec - zero.tv_usec) / 1000;
	return (ret);
}

void		skip_time(t_philo *philo, t_timer end)
{
	while (get_times(philo->data->zero) < end)
		usleep(10);
}

int			ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}
