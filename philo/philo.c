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
        return (1);
    philos = sanitize_input(argc, argv);
}

t_philo *init_philos(int num_philos, int meal_time, int sleep_time, int nbr_meals)
{
    t_philo *philos;
    int i;

    philos = malloc(sizeof(t_philo) * num_philos);
    if (!philos)
        return (philos);
    i = 0;
    while (i < num_philos)
    {
        philos[i].id = i + 1;
        philos[i].last_eat_time = meal_time;
        philos[i].state = THINKING;
        philos[i].eat_count = nbr_meals;
        philos[i].left_fork = i;
        philos[i].right_fork = i + 1;
        philos[i].thread = 0;
        i++;
    }
    return (philos);
}
