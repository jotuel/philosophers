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
#include <inttypes.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>

enum e_philo_state
{
    EATING,
    SLEEPING,
    THINKING,
    DEAD,
    FORK,
    DONE
};

typedef struct s_philo
{
    int id;
    unsigned long start;
    unsigned long sleep_time;
    unsigned long eat_time;
    unsigned long last_eat_time;
    unsigned long lifetime;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    enum e_philo_state state;
    int eat_count;
    struct timeval last_meal;
    pthread_t thread;
} t_philo;

t_philo *init_philos(int arguments[5], t_philo *philos, int i);
t_philo *sanitize_input(int argc, char **argv, t_philo *philos);
pthread_mutex_t *init_mutexes(int num_philos);
size_t	get_current_time(void);
void print_status(t_philo *philo, char *status, bool destroy);
void create_threads(t_philo *philos);
void join_threads(t_philo *philos);
void free_philos(t_philo *philos);
void eating(t_philo *philo);
void sleeping(t_philo *philo);
void thinking(t_philo *philo);

#endif
