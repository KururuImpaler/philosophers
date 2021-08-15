/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:33:38 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 09:51:00 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int			arg_not_digit(char **arg)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	while (arg[++i])
	{
		n = 0;
		j = -1;
		while (arg[i][++j] != '\0')
		{
			if (arg[i][j] < '0' || arg[i][j] > '9')
				return (1);
			if (arg[i][j] == '0')
				n++;
		}
		if (j == 0 || n == j)
			return (1);
	}
	return (0);
}

static int			get_int(char *s)
{
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr = nbr * 10 + s[i] - '0';
		i++;
	}
	return (nbr);
}

static t_timer		get_time(char *s)
{
	int			i;
	t_timer		nbr;

	i = 0;
	nbr = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr = nbr * 10 + s[i] - '0';
		i++;
	}
	return (nbr);
}

int					get_args(t_data *data, int size, char **arg)
{
	if (size < 5 || size > 6 || arg_not_digit(arg))
		return (1);
	data->num = get_int(arg[1]);
	data->t_live = get_time(arg[2]);
	data->t_eat = get_time(arg[3]);
	data->t_sleep = get_time(arg[4]);
	data->lim_eat = (size == 6) ? get_int(arg[5]) : 0;
	data->args = size;
	gettimeofday(&data->zero, NULL);
	if ((data->args == 6 && !data->lim_eat) || data->num < 2)
		return (1);
	return (0);
}
