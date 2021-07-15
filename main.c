/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbeech <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 12:02:46 by vbeech            #+#    #+#             */
/*   Updated: 2021/07/08 12:02:48 by vbeech           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int code)
{
	if (code == 1)
		printf("Error: wrong number of arguments\n");
	else if (code == 2)
		printf("Error: invalid arguments\n");
	else if (code == 3)
		printf("Malloc error\n");
	else if (code == 4)
		printf("Threads error\n");
	return (1);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (print_error(2));
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	init_struct(t_all *all, int argc, char **argv)
{
	all->num = ft_atoi(argv[1]);
	all->die = (uint64_t)ft_atoi(argv[2]);
	all->eat = (uint64_t)ft_atoi(argv[3]);
	all->sleep = (uint64_t)ft_atoi(argv[4]);
	if (all->num < 1 || all->die < 60 || all->eat < 60 || all->sleep < 60)
		return (print_error(2));
	if (argc == 6)
	{
		all->min_eat = ft_atoi(argv[5]);
		if (all->min_eat < 1)
			return (print_error(2));
	}
	else
		all->min_eat = 0;
	all->philos = (t_philos *)malloc(sizeof(t_philos) * all->num);
	if (!all->philos)
		return (print_error(3));
	all->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* all->num);
	if (!all->m_forks)
	{
		free(all->philos);
		return (print_error(3));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_all	all;

	if (argc != 5 && argc != 6)
		return (print_error(1));
	if (check_args(argv) == 1)
		return (1);
	if (init_struct(&all, argc, argv) == 1)
		return (1);
	init_philos(&all);
	if (start_simulation(&all) == 1)
	{
		clear_all(&all);
		return (1);
	}
	pthread_mutex_lock(&all.m_exit);
	pthread_mutex_unlock(&all.m_exit);
	clear_all(&all);
	return (0);
}
