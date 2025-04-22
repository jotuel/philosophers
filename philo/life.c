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
#include <stdatomic.h>

void	check_pulse(unsigned long last_meal,
		unsigned long time_btw_meals, t_philo *philo)
{
	if (*(philo->death))
		philo->state = DONE;
	else if (get_current_time() - last_meal > time_btw_meals)
	{
		print_status(philo, "has died", false);
		philo->state = DEAD;
		*philo->death = true;
	}
	else if(*(philo->death))
		philo->state = DONE;
}

void	print_status(t_philo *philo, char *status, bool destroy)
{
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	static char				*fmt = "%ld %d %s\n";

	if (destroy)
	{
		pthread_mutex_destroy(&mtx);
		return ;
	}
	pthread_mutex_lock(&mtx);
	printf(fmt, get_current_time() - philo->start, philo->id, status);
	pthread_mutex_unlock(&mtx);
}

void	sleeping(t_philo *philo)
{
	check_pulse(philo->last_eat_time, philo->lifetime, philo);
	if (philo->state == DEAD || philo->state == DONE)
		return ;
	print_status(philo, "is sleeping", false);
	usleep(philo->sleep_time * 1000);
	philo->state = THINKING;
}

void	thinking(t_philo *philo)
{
	check_pulse(philo->last_eat_time, philo->lifetime, philo);
	if (philo->state == DEAD || philo->state == DONE)
		return ;
	print_status(philo, "is thinking", false);
	usleep(20);
	philo->state = EATING;
}

void	eating(t_philo *philo)
{
	check_pulse(philo->last_eat_time, philo->lifetime, philo);
	if (philo->left_fork == philo->right_fork)
		return ;
	fork_lock(philo);
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
	if (philo->state == DEAD || philo->state == DONE)
		return ;
	philo->state = SLEEPING;
}
