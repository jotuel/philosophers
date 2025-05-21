/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:55:30 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/20 17:55:30 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <inttypes.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

#define FMT "%ld %d %s\n"

enum				e_philo_state
{
    DONE,
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FORK,
};

typedef struct s_philo
{
	atomic_int					id;
	bool						group;
	atomic_size_t				*start;
	atomic_size_t				sleep_time;
	atomic_size_t				eat_time;
	atomic_size_t				last_eat_time;
	atomic_size_t				lifetime;
	pthread_mutex_t				fork;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	_Atomic enum e_philo_state	state;
	int							eat_count;
	struct timeval				last_meal;
	pthread_t					thread;
	atomic_bool					*death;
	atomic_bool					*begin;
}					t_philo;

t_philo				*init_philos(int arguments[5], t_philo *philos);
t_philo				*sanitize_input(int argc, char **argv, t_philo *philos);
void	            *philosopher(void *state);
void	            *observer(void *arg);
void				fork_lock(t_philo *philo);
void				check_pulse(atomic_size_t last_meal,
						atomic_size_t time_btw_meals, t_philo *philo);
pthread_mutex_t		*init_mutexes(int num_philos);
size_t				get_time(void);
void				print_status(t_philo *philo, char *status, bool destroy);
void				create_threads(t_philo *philos);
void				join_threads(t_philo *philos);
void				free_philos(t_philo *philos);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);

#endif
