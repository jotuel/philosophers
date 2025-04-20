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

void print_status(t_philo *philo, char *status)
{
    struct timeval tv;

    if(gettimeofday(&tv, NULL))
        printf("%ld %d %s\n", tv.tv_usec - philo->start_time, philo->id, status);
}

void sleeping(t_philo *philo)
{
    print_status(philo, "is sleeping");
    usleep(philo->sleep_time * 1000);
}

void thinking(t_philo *philo)
{
    print_status(philo, "is thinking");
    usleep(20);
}

void eating(t_philo *philo)
{
    print_status(philo, "is eating");
    philo->eat_count++;
    usleep(philo->last_eat_time / philo->eat_count * 1000);
    philo->last_eat_time += philo->last_eat_time / philo->eat_count;
}
