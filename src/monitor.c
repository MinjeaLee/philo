/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:44:14 by mi                #+#    #+#             */
/*   Updated: 2023/09/18 03:09:34 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void set_finish(t_info *info, t_philosopher *philo)
{
	long long elapsed_time;

	// pthread_mutex_lock(&info->config.config_mutex);
	elapsed_time = get_time_elapsed(philo->last_eat_time, philo);
	if (elapsed_time > info->config.lifespan && !philo->finish_eat && !philo->in_eating)
	{
		info->config.finish_program = 1;
		pthread_mutex_lock(philo->print_mutex);
		printf("%lld %d died\n", get_current_time(philo), philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		// pthread_mutex_unlock(&info->config.config_mutex);
		return ;
	}
	if (info->config.num_finished == info->config.num_philosophers)
	{
		philo->config->finish_program = 1;
		philo->finish_eat = 1;
		pthread_mutex_lock(philo->print_mutex);
		printf("All philosophers ate %d times\n", info->config.min_eat_count);
		pthread_mutex_unlock(philo->print_mutex);
		// pthread_mutex_unlock(&info->config.config_mutex);
		return ;
	}
	// pthread_mutex_unlock(&info->config.config_mutex);
	return ;
}

int check_exit(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->config->config_mutex);
	if(philo->config->finish_program)
	{
		pthread_mutex_unlock(&philo->config->config_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->config->config_mutex);
	return (0);
}

void monitor(t_info *info)
{
	int i;

	i = 0;
	while(1)
	{
		i = 0;
		while(i < info->config.num_philosophers)
		{
			pthread_mutex_lock(&info->config.config_mutex);
			set_finish(info, &info->philosophers[i]);
			if (info->config.finish_program)
			{
				pthread_mutex_unlock(&info->config.config_mutex);
				cleanup(info);
				return ;
			}
			pthread_mutex_unlock(&info->config.config_mutex);
			i++;
		}
		ft_sleep(100);
	}
}
