/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:11:15 by mi                #+#    #+#             */
/*   Updated: 2023/09/18 02:57:44 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_think(t_philosopher *philo)
{
	print_status(philo, "is thinking");
}

int philo_eat(t_philosopher *philo)
{
	take_forks(philo);
	print_status(philo, "is eating");
	ft_sleep(philo->config->eat_duration);
	drop_forks(philo);
	pthread_mutex_lock(&philo->config->config_mutex);
	philo->last_eat_time = get_absolute_time();
	philo->eat_count++;
	if (philo->eat_count == philo->config->min_eat_count)
	{
		philo->finish_eat = 1;
		philo->config->num_finished++;
		pthread_mutex_unlock(&philo->config->config_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->config->config_mutex);
	return (0);
}

void philo_sleep(t_philosopher *philo)
{
	print_status(philo, "is sleeping");
	ft_sleep(philo->config->sleep_duration);
}

void take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}