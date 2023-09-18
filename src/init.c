/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:07:07 by mi                #+#    #+#             */
/*   Updated: 2023/09/18 02:25:33 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_config(t_info *info, int argc, char **argv)
{
	info->config.num_philosophers = ft_atoi(argv[1]);
	info->config.lifespan = ft_atoi(argv[2]);
	info->config.eat_duration = ft_atoi(argv[3]);
	info->config.sleep_duration = ft_atoi(argv[4]);
	if (argc == 6)
		info->config.min_eat_count = ft_atoi(argv[5]);
	else
		info->config.min_eat_count = INT_MAX;
	info->config.num_finished = 0;
	info->config.finish_program = 0;
	pthread_mutex_init(&info->config.config_mutex, NULL);
	init_time(info);
}

int alloc_mutex_init(t_info *info)
{
	int i;

	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
												info->config.num_philosophers);
	info->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * \
												info->config.num_philosophers);
	if (!info->forks || !info->philosophers)
		return (1);
	i = 0;
	while (i < info->config.num_philosophers)
	{
		pthread_mutex_init(&info->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&info->print_mutex, NULL);
	return (0);
}

void init_philosopher(t_info *info)
{
	int i;

	i = 0;
	while (i < info->config.num_philosophers)
	{
		info->philosophers[i].id = i;
		info->philosophers[i].config = &info->config;
		info->philosophers[i].left_fork = &info->forks[i];
		info->philosophers[i].right_fork = &info->forks[(i + 1) %
														info->config.num_philosophers];
		info->philosophers[i].print_mutex = &info->print_mutex;
		info->philosophers[i].eat_count = 0;
		info->philosophers[i].finish_eat = 0;
		info->philosophers[i].in_eating = 0;
		info->philosophers[i].g_start_time = info->g_start_time;
		info->philosophers[i].last_eat_time = get_current_time(&info->philosophers[i]);
		i++;
	}
}

int initialize(t_info *info, int argc, char **argv)
{
	
	init_config(info, argc, argv);
	if (alloc_mutex_init(info))
		return (1);
	init_philosopher(info);
	return (0);
}