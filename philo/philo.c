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
#include <pthread.h>

int main(int argc, char **argv)
{
    t_philo *philos;

    if (argc != 5 && argc != 6)
        return (EXIT_FAILURE);
    philos = sanitize_input(argc, argv);
    if (!philos)
        return (EXIT_FAILURE);
    create_threads(philos);
    join_threads(philos);
    free(philos);
}

t_philo *init_philos(int num_philos, int meal_time, int sleep_time, int nbr_meals)
{
    t_philo *philos;
    int i;

    philos = malloc(sizeof(t_philo) * num_philos + 1);
    memset(philos, 0, sizeof(t_philo) * num_philos + 1);
    if (!philos)
        return (philos);
    i = 0;
    while (i < num_philos)
    {
        philos[i].id = i + 1;
        philos[i].sleep_time = sleep_time;
        philos[i].eat_time = meal_time;
        philos[i].state = THINKING;
        philos[i].eat_count = nbr_meals;
        if (!pthread_mutex_init(philos[i].left_fork, NULL))
        {
            free_philos(philos);
            break ;
        }
        if (i++ > 0)
            philos[i].right_fork = philos[i - 1].left_fork;
    }
    return (philos);
}

static void *philosopher(void *state)
{
    t_philo *philo;
    enum e_philo_state status;

    philo = state;
    status = philo->state;
    while(true)
    {
        if (status == DONE)
            pthread_detach(philo->thread);
        if (status == DEAD)
            return (NULL);
        if (status == EATING)
            eating(philo);
        if (status == SLEEPING)
            sleeping(philo);
        if (status == THINKING)
            thinking(philo);
    }
}

void create_threads(t_philo *philos)
{
    int i;

    i = 0;
    while (philos[i].id)
    {
        philos[i].thread = pthread_create(&philos[i].thread, NULL, &philosopher, &philos[i]);
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
