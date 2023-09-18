/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 17:56:51 by mi                #+#    #+#             */
/*   Updated: 2023/09/18 01:11:14 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_atoi(const char *str)
{
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 0x9 && str[i] <= 0xd))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

void print_status(t_philosopher *philosopher, char *message)
{
	pthread_mutex_lock(&philosopher->config->config_mutex);
	if (philosopher->config->finish_program)
	{
		pthread_mutex_unlock(&philosopher->config->config_mutex);
		return ;
	}
	pthread_mutex_unlock(&philosopher->config->config_mutex);
	pthread_mutex_lock(philosopher->print_mutex);
	printf("%lld %d %s\n", get_current_time(philosopher), philosopher->id, message);	// TODO : get_current_time()
	pthread_mutex_unlock(philosopher->print_mutex);
}

