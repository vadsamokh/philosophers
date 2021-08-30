/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbeech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:39 by vbeech            #+#    #+#             */
/*   Updated: 2021/07/08 12:02:41 by vbeech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philos
{
	int				pos;
	int				eating;
	int				left_fork;
	int				right_fork;
	int				eat_ct;
	pthread_mutex_t	m_philo;
	pthread_mutex_t	m_eat_counter;
	uint64_t		latest_eat;
	uint64_t		not_eating;
	struct s_all	*all;
}	t_philos;

typedef struct s_all
{
	int				num;
	uint64_t		die;
	uint64_t		eat;
	uint64_t		sleep;
	int				min_eat;
	t_philos		*philos;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_exit;
	pthread_mutex_t	m_write;
	uint64_t		start;
}	t_all;

int			print_error(int code);
int			ft_atoi(const char *str);
uint64_t	get_time(void);
int			start_simulation(t_all *all);
void		*life(void *philo_copy);
void		init_philos(t_all *all);
void		take_forks(t_philos *philo);
void		put_forks_back(t_philos *philo);
void		eating(t_philos *philo);
void		print_message(t_philos *philo, int code);
void		clear_all(t_all *all);

#endif
