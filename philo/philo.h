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
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

enum e_philo_state
{
    PHILO_EAT,
    PHILO_SLEEP,
    PHILO_THINK,
    PHILO_DIE,
    PHILO_FORK,
    PHILO_DONE
};

typedef struct s_philo
{
    int id;
    int left_fork;
    int right_fork;
    int state;
    int eat_count;
    int last_eat_time;
    pthread_t thread;
} t_philo;

#endif
