/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbeech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 17:58:12 by vbeech            #+#    #+#             */
/*   Updated: 2021/07/10 17:58:15 by vbeech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	sum;

	sign = 1;
	sum = 0;
	while ((*str == '\t') || (*str == '\n') || (*str == '\v') || (*str == '\f')
		|| (*str == '\r') || (*str == ' '))
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		sum = sum * 10 + (sign * (*str - 48));
		str++;
	}
	return ((int)sum);
}

void	clear_all(t_all *all)
{
	int	i;

	i = 0;
	if (all->m_forks != NULL)
	{
		while (i < all->num)
		{
			pthread_mutex_destroy(&all->m_forks[i]);
			i++;
		}
		free(all->m_forks);
	}
	if (all->philos != NULL)
	{
		i = 0;
		while (i < all->num)
		{
			pthread_mutex_destroy(&all->philos[i].m_philo);
			pthread_mutex_destroy(&all->philos[i].m_eat_counter);
			i++;
		}
		free(all->philos);
	}
	pthread_mutex_destroy(&all->m_write);
	pthread_mutex_destroy(&all->m_exit);
}

/*int	philo_launch(pthread_t tid, t_philos *philo)
{
	if (pthread_create(&tid, NULL, &life, (void *)philo) != 0)
		return (print_error(4));
	pthread_detach(tid);
	return (0);
}*/
