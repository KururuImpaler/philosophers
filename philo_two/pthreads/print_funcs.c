/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:41:00 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/04 05:21:16 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int		ft_type(char *s, int type)
{
	int		i;
	char	*s1;
	int		len;

	i = -1;
	s1 = NULL;
	if (type == 1 && (len = 17))
		s1 = "has taken a fork\n";
	if (type == 2 && (len = 10))
		s1 = "is eating\n";
	if (type == 3 && (len = 12))
		s1 = "is sleeping\n";
	if (type == 4 && (len = 12))
		s1 = "is thinking\n";
	if (type == 5 && (len = 5))
		s1 = "died\n";
	while (++i < len)
		*s++ = s1[i];
	*s = '\0';
	return (len + 2);
}

static int		ft_itoa_2(int n, char *s, int type)
{
	int		len;
	int		n1;
	int		end;

	len = 1;
	n1 = n;
	while ((n1 /= 10))
		len++;
	end = len * -1;
	while (len-- > end)
	{
		*(s + len) = n % 10 + '0';
		len--;
		s++;
		n /= 10;
	}
	*s++ = ' ';
	return ((end * -1) + ft_type(s, type));
}

static int		ft_itoa_1(t_philo *philo, int type, int str)
{
	int		len;
	t_timer	t1;
	int		end;
	char	*s;

	len = 1;
	s = (str == 1) ? philo->s : philo->death;
	t1 = (str == 1) ? philo->now : philo->t_death;
	while ((t1 /= 10))
		len++;
	t1 = (str == 1) ? philo->now : philo->t_death;
	end = len * -1;
	while (len-- > end)
	{
		*(s + len) = t1 % 10 + '0';
		len--;
		s++;
		t1 /= 10;
	}
	*s++ = ' ';
	return ((end * -1) + ft_itoa_2(philo->num, s, type));
}

void			print(t_philo *philo, int type)
{
	int		len;

	sem_wait(philo->data->print);
	philo->now = get_times(philo->data->zero);
	len = ft_itoa_1(philo, type, 1);
	if (philo->stop)
		write(1, philo->s, len);
	sem_post(philo->data->print);
}

void			print_death(t_philo *philo)
{
	int		len;
	t_data	*data;

	data = philo->data;
	sem_wait(data->print);
	philo->t_death = get_times(data->zero);
	len = ft_itoa_1(philo, 5, 0);
	if (philo->stop && philo->t_death >= philo->end)
	{
		write(1, philo->death, len);
		len = 0;
		while (len++ < data->num)
			sem_post(data->stop);
		skip_time(philo, get_times(data->zero) + (data->num * 10));
	}
	sem_post(data->print);
}
