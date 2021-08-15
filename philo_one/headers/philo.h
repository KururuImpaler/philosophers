/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:41:50 by cmalt             #+#    #+#             */
/*   Updated: 2020/12/31 10:00:31 by cmalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

# include <sys/time.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>

typedef	long long	t_timer;

typedef struct		s_mutex
{
	int				mes_true;
	pthread_mutex_t	message;
	int				stop_true;
	pthread_mutex_t	stop;
	int				forks_true;
	pthread_mutex_t	*forks;
	int				eat_true;
	pthread_mutex_t	*eat;
}					t_mutex;

typedef struct		s_data
{
	int				num;
	t_timer			t_live;
	t_timer			t_eat;
	t_timer			t_sleep;
	int				args;
	int				lim_eat;
	struct timeval	zero;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*stop;
	pthread_mutex_t	*print;
	int				ret;
}					t_data;

typedef struct		s_philo
{
	int				num;
	int				stop;
	int				count;
	int				st_eat;
	char			*s;
	char			*death;
	t_data			*data;
	t_timer			start;
	t_timer			end;
	t_timer			now;
	t_timer			to_next;
	t_timer			t_death;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*eat;
	pthread_t		p_death;
	pthread_t		p_stop;
	struct s_philo	*next;
	struct s_philo	*prev;
}					t_philo;

/*
***INIT/PARSE_ARGS.C
*/

int					get_args(t_data *data, int size, char **arg);

/*
***INIT/FREE.C
*/

int					free_mutex(t_mutex *mutex);
int					free_philo(t_philo *philo, t_philo *new_philo);

/*
***INIT/CREATE_PTHREADS.C
*/

void				wait_philo(int i, pthread_t *pid, t_data *data, int n);
int					create_philo(void *(*func)(void *), void *arg,
					pthread_t *pid, int i);
void				init(t_data *data, t_philo **philo);

/*
***INIT/CREATE_MUTEX.C
*/

int					get_mutex(t_mutex *mutex, t_data *data, int num);

/*
***INIT/CREATE_LIST_PHILO.C
*/

int					init_philo(t_data *data, t_philo **philo, t_mutex *mutex);

/*
***PTHREADS/UTILS_FUNC.C
*/

t_timer				get_times(struct timeval zero);
void				skip_time(t_philo *philo, t_timer end);
int					ft_strlen(char *s);

/*
***PTHREADS/PTHREADS_FUNC.C
*/

void				*stop(void *arg);
void				*death(void *arg);
void				*philo_one(void *arg);
void				*limit_eat(void *arg);

/*
***PTHREADS/PRINT_FUNCS.C
*/

void				print(t_philo *philo, int type);
void				print_death(t_philo *philo);

/*
***PTHREADS/PHILO_DOING_FUNC.C
*/

void				philo_take(t_philo *philo);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);

/*
***PTHREADS/CREATE_MONITORS_THREADS.C
*/

int					create_pthread(t_philo *philo);
void				*fatal_philo(t_philo *philo, int i);

#endif
