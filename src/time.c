/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:31:29 by mi                #+#    #+#             */
/*   Updated: 2023/09/18 01:00:56 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long get_current_time(t_philosopher *philo)
{
	struct timeval current_time;
	long long elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = (current_time.tv_sec - philo->g_start_time.tv_sec) * 1000;
	elapsed_time += (current_time.tv_usec - philo->g_start_time.tv_usec) / 1000;
	return (elapsed_time);
}

long long get_time_elapsed(long long start_time, t_philosopher *philo)
{
	struct timeval current_time_struct;
	long long current_time;
	long long elapsed_time;

	gettimeofday(&current_time_struct, NULL);
	current_time = (current_time_struct.tv_sec * 1000) + (current_time_struct.tv_usec / 1000);
	current_time = current_time - ((philo->g_start_time.tv_sec * 1000) + (philo->g_start_time.tv_usec / 1000));
	elapsed_time = current_time - start_time;
	return (elapsed_time);
}

void init_time(t_info *info)
{
	gettimeofday(&info->g_start_time, NULL);
}

long long get_absolute_time(void)
{
	struct timeval current_time_struct;
	long long current_time;

	gettimeofday(&current_time_struct, NULL);
	current_time = (current_time_struct.tv_sec * 1000);
	current_time += (current_time_struct.tv_usec / 1000);
	return (current_time);
}

void ft_sleep(int time)
{
	long long curr;

	curr = get_absolute_time();
	while (get_absolute_time() - curr < time)
		usleep(100);
}