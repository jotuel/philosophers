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
#include <unistd.h>

static int	ft_atoi(char *s)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] || result < 0)
		result = 0;
	return (result);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		dprintf(STDERR_FILENO, "gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	free_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i].id)
	{
		pthread_exit(&philos[i].thread);
		pthread_mutex_destroy(philos[i].left_fork);
		i++;
	}
	free(philos);
	print_status(NULL, NULL, true);
}

t_philo	*sanitize_input(int argc, char **argv, t_philo *philos)
{
	int	arguments[5];

	arguments[0] = ft_atoi(argv[1]);
	arguments[1] = ft_atoi(argv[2]);
	arguments[2] = ft_atoi(argv[3]);
	arguments[3] = ft_atoi(argv[4]);
	if (argc == 6)
		arguments[4] = ft_atoi(argv[5]);
	else
		arguments[4] = -1;
	if (arguments[0] && arguments[1] && arguments[2] && arguments[3]
		&& arguments[4])
		philos = init_philos(arguments, philos);
	if (!philos)
		dprintf(STDERR_FILENO, "Error: Failed to initialize philosophers.\n");
	return (philos);
}

void	fork_lock(t_philo *philo)
{
	philo->state = FORK;
	if (philo->group)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork", false);
		pthread_mutex_lock(philo->right_fork);
		philo->state = EATING;
		print_status(philo, "has taken a fork", false);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork", false);
		pthread_mutex_lock(philo->left_fork);
		philo->state = EATING;
		print_status(philo, "has taken a fork", false);
	}
	print_status(philo, "is eating", false);
}
