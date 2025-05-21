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
#include <sys/cdefs.h>
#include <unistd.h>
#include <assert.h>

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6) {
		dprintf(STDERR_FILENO,
		"Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat>"
		" <time_to_sleep> [<number_of_times_each_philosopher_must_eat>]\n");
		return (EXIT_FAILURE);
	}
	t_philo *philos = NULL;
	philos = sanitize_input(argc, argv, philos);
	if (!philos)
		return (EXIT_FAILURE);
	create_threads(philos);
	join_threads(philos);
	free(philos);
}

t_philo	*init_philos(int arguments[5], t_philo *philos)
{
	static atomic_size_t utc;
	utc = get_time();
	philos = malloc(sizeof(t_philo) * (arguments[0] + 1));
	assert(philos);
	memset(philos, 0, sizeof(t_philo) * (arguments[0] + 1));
	for (int i = 0; i < arguments[0]; i++) {
		philos[i].id = i + 1;
		philos[i].start = &utc;
		philos[i].last_eat_time = *philos[i].start;
		philos[i].sleep_time = arguments[3];
		philos[i].lifetime = arguments[1];
		philos[i].eat_time = arguments[2];
		philos[i].eat_count = arguments[4];
		philos[i].state = FORK;
		philos[i].left_fork = &philos[i].fork;
		if (pthread_mutex_init(philos[i].left_fork, NULL))
			return (free_philos(philos), NULL);
		philos[i + 1].right_fork = philos[i].left_fork;
	}
	philos[0].right_fork = philos[arguments[0] - 1].left_fork;
	return (philos);
}

void	print_status(t_philo *philo, char *status, bool destroy)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mtx);
    if (!*(philo->death) || ( philo->death && philo->state == DEAD ) )
    	printf(FMT, get_time() - *philo->start, philo->id, status);
    pthread_mutex_unlock(&mtx);
	if (destroy)
		pthread_mutex_destroy(&mtx);
}

void	create_threads(t_philo *philos)
{
	static atomic_bool	death = false, begin = false;
	int i;
	for (i = 0; philos[i].id; i++) {
		philos[i].death = &death;
		philos[i].begin = &begin;
		if (pthread_create(&philos[i].thread, NULL, &philosopher, &philos[i])) {
			dprintf(STDERR_FILENO, "Error: pthread_create\n");
			death = true;
			begin = true;
			return ;
		}
	}
	*philos[0].start = get_time();
	begin = true;
	if (pthread_create(&philos[i].thread, NULL, &observer, philos)) {
		dprintf(STDERR_FILENO, "Error: pthread_create\n");
		death = true;
		return ;
	}
}

void	join_threads(t_philo *philos)
{
    int i;
	for (i = 0; philos[i].id; i++)
		pthread_join(philos[i].thread, NULL);
	pthread_join(philos[i].thread, NULL);
}
