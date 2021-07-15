/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbeech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:08:16 by vbeech            #+#    #+#             */
/*   Updated: 2021/07/13 14:08:17 by vbeech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philos *philo, int code)
{
	static int	dead_flag = 0;

	pthread_mutex_lock(&philo->all->m_write);
	if (dead_flag == 0)
	{
		if (code == 5 || code == 6)
			dead_flag = 1;
		if (code != 5)
			printf("[%llu ms]\t%d ", get_time() - philo->all->start,
				philo->pos + 1);
		else
			printf("All philosophers have successfully eaten %d times. "
				   "Finished simulation.\n", philo->all->min_eat);
		if (code == 1)
			printf("is eating\n");
		else if (code == 2)
			printf("is sleeping\n");
		else if (code == 3)
			printf("has taken a fork\n");
		else if (code == 4)
			printf("is thinking\n");
		else if (code == 6)
			printf("died\n");
	}
	pthread_mutex_unlock(&philo->all->m_write);
}

void	take_forks(t_philos *philo)
{
	pthread_mutex_lock(&philo->all->m_forks[philo->left_fork]);
	print_message(philo, 3);
	pthread_mutex_lock(&philo->all->m_forks[philo->right_fork]);
	print_message(philo, 3);
}

void	put_forks_back(t_philos *philo)
{
	print_message(philo, 2);
	pthread_mutex_unlock(&philo->all->m_forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->all->m_forks[philo->right_fork]);
	usleep(philo->all->sleep * 1000);
}

void	eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->m_philo);
	print_message(philo, 1);
	philo->latest_eat = get_time();
	philo->eating = 1;
	philo->not_eating = philo->latest_eat + philo->all->die;
	usleep(philo->all->eat * 1000);
	philo->eat_ct++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->m_philo);
	pthread_mutex_unlock(&philo->m_eat_counter);
}
