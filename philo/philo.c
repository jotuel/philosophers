/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:55:25 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/20 17:55:25 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_philo *philos;

    if (argc != 5 && argc != 6)
        return (EXIT_FAILURE);
    philos = NULL;
    philos = sanitize_input(argc, argv, philos);
    if (!philos)
        return (EXIT_FAILURE);
    create_threads(philos);
    join_threads(philos);
    free(philos);
}

t_philo *init_philos(int arguments[5], t_philo *philos, int i)
{
    philos = malloc(sizeof(t_philo) * (arguments[0] + 1));
    if (!philos)
        return (philos);
    memset(philos, 0, sizeof(t_philo) * (arguments[0] + 1));
    while (i < arguments[0])
    {
        philos[i].id = i + 1;
        philos[i].sleep_time = arguments[3];
        philos[i].lifetime = arguments[1];
        philos[i].eat_time = arguments[2];
        philos[i].eat_count = arguments[4];
        philos[i].state = THINKING;
        philos[i].start = get_current_time();
        philos[i].last_eat_time = philos[i].start;
        philos[i].left_fork = malloc(sizeof(pthread_mutex_t));
        if (!philos[i].left_fork)
            return (free_philos(philos), NULL);
        if (pthread_mutex_init(philos[i].left_fork, NULL))
            return (free_philos(philos), NULL);
        i++;
        philos[i].right_fork = philos[i - 1].left_fork;
    }
    philos[0].right_fork = philos[arguments[0] - 1].left_fork;
    return (philos);
}

static void *philosopher(void *state)
{
    t_philo *philo;

    philo = state;
    while(true)
    {
        if (philo->state == DONE || philo->state == DEAD)
            pthread_exit(NULL);
        else if (philo->state == EATING)
            eating(philo);
        else if (philo->state == SLEEPING)
            sleeping(philo);
        else if (philo->state == THINKING)
            thinking(philo);
    }
}

void create_threads(t_philo *philos)
{
    int i;

    i = 0;
    while (philos[i].id)
    {
        if(pthread_create(&philos[i].thread, NULL, &philosopher, &philos[i]))
            return ;
        else
            i++;
    }
}

void join_threads(t_philo *philos)
{
    int i;

    i = 0;
    while (philos[i].id)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
}
