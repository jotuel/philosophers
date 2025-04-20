/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtuomi <jtuomi@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:55:43 by jtuomi            #+#    #+#             */
/*   Updated: 2025/04/20 18:04:58 by jtuomi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_atoi(char *s)
{
    int result = 0;
    int i = 0;

    while (s[i] >= '0' && s[i] <= '9')
    {
        result = result * 10 + (s[i] - '0');
        i++;
    }
    return (result);
}

t_philo *sanitize_input(int argc, char **argv)
{
    t_philo *sophers;
    int philos;
    int eat_time;
    int sleep_time;
    int nbr_meals;

    sophers = NULL;
    philos = ft_atoi(argv[1]);
    eat_time = ft_atoi(argv[2]);
    sleep_time = ft_atoi(argv[3]);
    if (argc == 5)
        nbr_meals = ft_atoi(argv[4]);
    else
        nbr_meals = -1;
    if (philos && eat_time && sleep_time && nbr_meals)
        sophers = init_philos(philos, eat_time, sleep_time, nbr_meals);
    if (!sophers)
    {
        printf("Error: Failed to initialize philosophers.\n");
        exit(EXIT_FAILURE);
    }
    return (sophers);
}
