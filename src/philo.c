/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:49:32 by mi                #+#    #+#             */
/*   Updated: 2023/09/18 03:02:53 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philosopher_routine(void *arg)
{
	t_philosopher *philosopher = (t_philosopher *)arg;
	
	if (philosopher->config->num_philosophers == 1)
	{
		take_forks(philosopher);
		return (NULL);
	}
	if (philosopher->id % 2 == 0)
		ft_sleep(philosopher->config->eat_duration);
	while (1)
	{
		if(philo_eat(philosopher))
			break ;
		if (check_exit(philosopher))
			break ;
		philo_sleep(philosopher);
		philo_think(philosopher);
	}
	return (NULL);
}

void start_philosopher_threads(t_info *info)
{
	int i;
	pthread_t *threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * info->config.num_philosophers);
	i = 0;
	while (i < info->config.num_philosophers)
	{
		pthread_create(&threads[i], NULL, philosopher_routine, &info->philosophers[i]);
		i++;
	}
	monitor(info);
	free(threads);
}

void cleanup(t_info *info)
{
	int i;

	i = 0;
	while(i < info->config.num_philosophers)
	{
		pthread_join(info->philosophers[i].thread, NULL);
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(info->philosophers[i].print_mutex);
		i++;
	}
	
	pthread_mutex_destroy(&info->config.config_mutex);
	free(info->forks);
	free(info->philosophers);
}

void f()
{
	system("leaks philo");
}


int main(int argc, char **argv)
{
	t_info info;
	// atexit(f);
	
	memset(&info, 0, sizeof(t_info));
	if (argc < 5 || argc > 6)
		return (1);
	initialize(&info, argc, argv);
	start_philosopher_threads(&info);
	return (0);
}

// TODO : 못 먹으면 죽어야 함
// TODO : 한명이 죽으면 프로그램이 종료되어야 함
// TODO : 각자 먹는 횟수가 정해진 경우 다 먹으면 안 먹어야함