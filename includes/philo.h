/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:36:21 by mi                #+#    #+#             */
/*   Updated: 2023/09/18 03:01:59 by mi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_config
{
	int num_philosophers; // 철학자의 수
	int lifespan;		  // 철학자의 수명
	int eat_duration;	  // 밥을 먹는데 걸리는 시간 (밀리초 단위)
	int sleep_duration;	  // 잠자는 시간 (밀리초 단위)
	int min_eat_count;	  // 각 철학자가 최소한 밥을 먹어야 하는 횟수
	int num_finished;	  // 밥을 다 먹은 철학자의 수
	int finish_program;	  // 프로그램 종료 여부
	pthread_mutex_t config_mutex;
} t_config;

typedef struct s_philosopher
{
	int id;						  // 철학자 ID
	pthread_t thread;			  // 철학자 스레드
	pthread_mutex_t *left_fork;	  // 왼쪽 포크
	pthread_mutex_t *right_fork;  // 오른쪽 포크
	pthread_mutex_t *print_mutex; // 출력 동기화를 위한 뮤텍스
	t_config *config;			  // 철학자 설정 정보에 대한 참조
	int eat_count;				  // 철학자가 밥을 먹은 횟수
	int finish_eat;				//
	int in_eating;				  // 밥을 먹는 중인지 여부
	struct timeval g_start_time;	// 현재 시간 출력하기 위함, 시작 시간 저장 
	long long last_eat_time; // 마지막으로 밥을 먹은 시간
} t_philosopher;

typedef struct s_info
{
	t_config config;			 // 철학자 관련 설정 정보
	pthread_mutex_t *forks;		 // 포크 뮤텍스 배열
	pthread_mutex_t print_mutex; // 출력 동기화를 위한 뮤텍스
	struct timeval g_start_time; // 철학자들이 밥을 먹기 시작한 시간
	t_philosopher *philosophers; // 철학자 배열
} t_info;

// utils.c
int ft_atoi(const char *str);
void print_status(t_philosopher *philosopher, char *message);

// init.c
int initialize(t_info *info, int argc, char **argv);

// philo.c
void *philosopher_routine(void *arg);
void cleanup(t_info *info);

// status.c
void philo_think(t_philosopher *philo);
int philo_eat(t_philosopher *philo);
void philo_sleep(t_philosopher *philo);
void take_forks(t_philosopher *philo);
void drop_forks(t_philosopher *philo);

// time.c
void init_time(t_info *info);
long long get_current_time(t_philosopher *philo);
long long get_time_elapsed(long long start_time, t_philosopher *philo);
void ft_sleep(int num);
long long get_absolute_time(void);

// monitor.c
void monitor(t_info *info);
int check_exit(t_philosopher *philo);

#endif