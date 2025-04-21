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

static void check_pulse(enum e_philo_state *state, unsigned long last_meal,
    unsigned long time_btw_meals)
{
    if (get_current_time() - last_meal > time_btw_meals)
        *state = DEAD;
}

void print_status(t_philo *philo, char *status, bool destroy)
{
    static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

    if (destroy)
    {
        pthread_mutex_destroy(&mtx);
        return ;
    }
    pthread_mutex_lock(&mtx);
    printf("%ld %d %s\n", get_current_time() - philo->start, philo->id, status);
    pthread_mutex_unlock(&mtx);
}

void sleeping(t_philo *philo)
{
    check_pulse(&philo->state, philo->last_eat_time, philo->lifetime);
    if (philo->state != DEAD)
        print_status(philo, "is sleeping", false);
    usleep(philo->sleep_time * 1000);
    philo->state = THINKING;
}

void thinking(t_philo *philo)
{
    check_pulse(&philo->state, philo->last_eat_time, philo->lifetime);
    if (philo->state != DEAD)
        print_status(philo, "is thinking", false);
    usleep(20);
    philo->state = EATING;
}

void eating(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    check_pulse(&philo->state, philo->last_eat_time, philo->lifetime);
    if (philo->state != DEAD)
        print_status(philo, "has taken a fork", false);
    pthread_mutex_lock(philo->right_fork);
    check_pulse(&philo->state, philo->last_eat_time, philo->lifetime);
    if (philo->state != DEAD)
        print_status(philo, "has taken a fork", false);
    check_pulse(&philo->state, philo->last_eat_time, philo->lifetime);
    if (philo->state != DEAD)
        print_status(philo, "is eating", false);
    usleep(philo->eat_time * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    philo->eat_count--;
    if (!philo->eat_count)
    {
        philo->state = DONE;
        return ;
    }
    philo->last_eat_time = get_current_time();
    philo->state = SLEEPING;
}
