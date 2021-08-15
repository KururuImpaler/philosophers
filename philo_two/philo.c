/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:32:42 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 11:36:21 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int size, char **arg)
{
	t_sem			semaphore;
	t_philo			*philo;
	t_data			data;

	philo = NULL;
	if (get_args(&data, size, arg) || get_sem(&semaphore, &data, data.num))
	{
		write(1, "bad args\n", ft_strlen("bad args\n"));
		return (0);
	}
	init_philo(&data, &philo, &semaphore);
	init(&data, &philo);
	if (data.ret)
		write(1, "fatal philo\n", ft_strlen("fatal philo\n"));
	free_semaphore(&semaphore);
	free_philo(philo, NULL);
	return (0);
}
