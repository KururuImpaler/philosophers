/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalt <cmalt@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 09:41:50 by cmalt             #+#    #+#             */
/*   Updated: 2021/01/03 10:52:57 by cmalt            ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef	long long	t_timer;

typedef struct		s_sem
{
	int				mes_true;
	sem_t			*message;
	int				stop_true;
	sem_t			*stop;
	int				forks_true;
	sem_t			*forks;
	int				eat_true;
	sem_t			*eat;
	int				waiter_true;
	sem_t			*waiter;
}					t_sem;

typedef struct		s_data
{
	int				num;
	t_timer			t_live;
	t_timer			t_eat;
	t_timer			t_sleep;
	int				args;
	int				lim_eat;
	struct timeval	zero;
	sem_t			*eat;
	sem_t			*fork;
	sem_t			*stop;
	sem_t			*print;
	sem_t			*waiter;
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
	sem_t			*fork;
	sem_t			*eat;
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

int					free_semaphore(t_sem *semaphore);
int					free_philo(t_philo *philo, t_philo *new_philo);

/*
***INIT/CREATE_PTHREADS.C
*/

int					wait_philo(int i, pid_t *pid, t_data *data, int n);
int					create_philo(int (*func)(void *), void *arg, pid_t *pid,
					int i);
void				init(t_data *data, t_philo **philo);

/*
***INIT/CREATE_SEMAPHORE.C
*/

int					get_sem(t_sem *semaphore, t_data *data, int num);

/*
***INIT/CREATE_LIST_PHILO.C
*/

int					init_philo(t_data *data, t_philo **philo, t_sem *semaphore);

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
int					limit_eat(void *arg);
int					philo_three(void *arg);

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
int					fatal_philo(t_philo *philo, int i);

#endif
