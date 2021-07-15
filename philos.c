/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbeech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 15:49:40 by vbeech            #+#    #+#             */
/*   Updated: 2021/07/08 15:49:42 by vbeech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_all *all)
{
	int	i;

	i = 0;
	pthread_mutex_init(&all->m_write, NULL);
	pthread_mutex_init(&all->m_exit, NULL);
	pthread_mutex_lock(&all->m_exit);
	while (i < all->num)
	{
		all->philos[i].pos = i;
		all->philos[i].eating = 0;
		all->philos[i].left_fork = i;
		all->philos[i].right_fork = i + 1;
		if (all->philos[i].right_fork == all->num)
			all->philos[i].right_fork = 0;
		all->philos[i].eat_ct = 0;
		all->philos[i].all = all;
		pthread_mutex_init(&all->philos[i].m_philo, NULL);
		pthread_mutex_init(&all->m_forks[i], NULL);
		pthread_mutex_init(&all->philos[i].m_eat_counter, NULL);
		pthread_mutex_lock(&all->philos[i].m_eat_counter);
		i++;
	}
}

void	*eat_counter(void *all_copy)
{
	t_all	*all;
	int		i;
	int		count;

	all = (t_all *)all_copy;
	count = 0;
	while (count < all->min_eat)
	{
		i = 0;
		while (i < all->num)
		{
			pthread_mutex_lock(&all->philos[i].m_eat_counter);
			i++;
		}
		count++;
	}
	i--;
	print_message(&all->philos[i], 5);
	pthread_mutex_unlock(&all->m_exit);
	return ((void *)0);
}

void	*death_monitor(void *philo_copy)
{
	t_philos	*philo;

	philo = (t_philos *)philo_copy;
	while (1)
	{
		pthread_mutex_lock(&philo->m_philo);
		if (philo->eating == 0 && get_time() > philo->not_eating)
		{
			print_message(philo, 6);
			pthread_mutex_unlock(&philo->m_philo);
			pthread_mutex_unlock(&philo->all->m_exit);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->m_philo);
		usleep(1000);
	}
}

void	*life(void *philo_copy)
{
	t_philos	*philo;
	pthread_t	tid;

	philo = (t_philos *)philo_copy;
	philo->latest_eat = get_time();
	philo->not_eating = philo->latest_eat + philo->all->die;
	if (pthread_create(&tid, NULL, &death_monitor, philo_copy) != 0)
		return ((void *)1);
	pthread_detach(tid);
	while (1)
	{
		take_forks(philo);
		eating(philo);
		put_forks_back(philo);
		print_message(philo, 4);
	}
	return ((void *)0);
}

int	start_simulation(t_all *all)
{
	pthread_t	tid;
	int			i;

	all->start = get_time();
	if (all->min_eat > 0)
	{
		if (pthread_create(&tid, NULL, &eat_counter, (void *)all) != 0)
			return (print_error(4));
		pthread_detach(tid);
	}
	i = 0;
	while (i < all->num)
	{
		if (pthread_create(&tid, NULL, &life, (void *)(&all->philos[i])) != 0)
			return (print_error(4));
		pthread_detach(tid);
		usleep(100);
		//if (philo_launch(tid, &all->philos[i]) == 1)
		//	return (1);
		i++;
	}
	/*i = 1;
	while (i < all->num)
	{
		if (pthread_create(&tid, NULL, &life, (void *)(&all->philos[i])) != 0)
			return (print_error(4));
		pthread_detach(tid);
		if (philo_launch(tid, &all->philos[i]) == 1)
			return (print_error(4));
		i = i + 2;
	}*/
	return (0);
}
