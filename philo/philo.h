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
    int left_fork;
    int right_fork;
    enum e_philo_state state;
    int eat_count;
    int last_eat_time;
    pthread_t thread;
} t_philo;

t_philo *init_philos(int num_philos, int meal_time, int sleep_time, int nbr_meals);
t_philo *sanitize_input(int argc, char **argv);

#endif
