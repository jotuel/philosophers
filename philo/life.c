/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 19:46:48 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/20 19:46:48 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void check_pulse(enum e_philo_state *state, int last_meal, int time_btw_meals)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (tv.tv_usec - last_meal > time_btw_meals)
        *state = DEAD;
}

void print_status(t_philo *philo, char *status)
{
    static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
    struct timeval tv;

    pthread_mutex_lock(&mtx);
    if (gettimeofday(&tv, NULL))
        printf("%ld %d %s\n", tv.tv_usec - philo->start_time, philo->id, status);
    pthread_mutex_unlock(&mtx);
}

void sleeping(t_philo *philo)
{
    check_pulse(&philo->state, philo->last_eat_time, philo->eat_time);
    if (philo->state != DEAD)
        print_status(philo, "is sleeping");
    usleep(philo->sleep_time * 1000);
}

void thinking(t_philo *philo)
{
    check_pulse(&philo->state, philo->last_eat_time, philo->eat_time);
    if (philo->state != DEAD)
        print_status(philo, "is thinking");
    usleep(20);
}

void eating(t_philo *philo)
{
    struct timeval tv;

    check_pulse(&philo->state, philo->last_eat_time, philo->eat_time);
    if (philo->state != DEAD)
    {
        pthread_mutex_lock(&philo->left_fork);
        pthread_mutex_lock(&philo->right_fork);
        print_status(philo, "is eating");
        pthread_mutex_unlock(&philo->left_fork);
        pthread_mutex_unlock(&philo->right_fork);
    }
    philo->eat_count--;
    if (!philo->eat_count)
    {
        philo->state = DONE;
        return ;
    }
    usleep(philo->eat_time * 1000);
    gettimeofday(&tv, NULL);
    philo->last_eat_time = tv.tv_usec;
}
