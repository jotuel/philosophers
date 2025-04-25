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

int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		write(2,
			"Usage: ./philo <number_of_philosophers> <time_to_die "
			"<time_to_eat> <time_to_sleep> "
			"[<number_of_times_each_philosopher_must_eat>]\n",
			129);
		return (EXIT_FAILURE);
	}
	philos = NULL;
	philos = sanitize_input(argc, argv, philos);
	if (!philos)
	{
		write(2, "Error: Failed to allocate memory for philosophers\n", 51);
		return (EXIT_FAILURE);
	}
	create_threads(philos, 0);
	join_threads(philos, 0);
	free(philos);
}

t_philo	*init_philos(int arguments[5], t_philo *philos, int i)
{
	philos = malloc(sizeof(t_philo) * (arguments[0] + 1));
	if (!philos)
		return (philos);
	memset(philos, 0, sizeof(t_philo) * (arguments[0] + 1));
	while (i < arguments[0])
	{
		philos[i].id = i + 1;
		philos[i].start = get_time();
		philos[i].last_eat_time = philos[i].start;
		philos[i].sleep_time = arguments[3];
		philos[i].lifetime = arguments[1];
		philos[i].eat_time = arguments[2];
		philos[i].eat_count = arguments[4];
		philos[i].state = THINKING;
		philos[i].left_fork = &philos[i].fork;
		if (pthread_mutex_init(philos[i].left_fork, NULL))
			return (free_philos(philos), NULL);
		i++;
		philos[i].right_fork = philos[i - 1].left_fork;
	}
	philos[0].right_fork = philos[arguments[0] - 1].left_fork;
	return (philos);
}

void	print_status(t_philo *philo, char *status, bool destroy)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	static char				*fmt = "%ld %d %s\n";

	pthread_mutex_lock(&mtx);
	if (!*(philo->death) || philo->state == DEAD)
		printf(fmt, get_time() - philo->start, philo->id, status);
	pthread_mutex_unlock(&mtx);
	if (destroy)
		pthread_mutex_destroy(&mtx);
}

void	*philosopher(void *state);
void	*observer(void *arg);

void	create_threads(t_philo *philos, int i)
{
	static atomic_bool	death = false;
	static atomic_bool	begin = false;

	while (philos[i].id)
	{
		philos[i].death = &death;
		philos[i].begin = &begin;
		if (pthread_create(&philos[i].thread, NULL, &philosopher, &philos[i]))
		{
			write(2, "Error: pthread_create\n", 25);
			death = true;
			begin = true;
			return ;
		}
		i++;
	}
	begin = true;
	if (pthread_create(&philos[i].thread, NULL, &observer, philos))
	{
		write(2, "Error: pthread_create\n", 25);
		death = true;
		return ;
	}
}

void	join_threads(t_philo *philos, int i)
{
	while (philos[i].id)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(philos[i].thread, NULL);
}
