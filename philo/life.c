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

void	*observer(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	while (!*philo[0].death)
	{
		while (philo[i].id)
		{
			if (get_time() - philo[i].last_eat_time > philo[i].lifetime)
			{
				philo[i].state = DEAD;
				*philo[i].death = true;
				print_status(&philo[i], "died", false);
				philo[i].state = DONE;
			}
			i++;
		}
		i = 0;
		usleep(1000);
	}
	return (NULL);
}

void	*philosopher(void *state)
{
	t_philo	*philo;

	philo = state;
	if (philo->id % 2)
	{
		philo->group = true;
		usleep(philo->eat_time * 1000);
	}
	while (!*philo->begin)
		usleep(1000);
	philo->last_eat_time = *philo->start;
	while (!*philo->death)
	{
		if (philo->state == FORK)
			eating(philo);
		else if (philo->state == SLEEPING)
			sleeping(philo);
		else if (philo->state == THINKING)
			thinking(philo);
		else if (philo->state == DONE)
			break ;
	}
	return (NULL);
}

void	sleeping(t_philo *philo)
{
	print_status(philo, "is sleeping", false);
	usleep(philo->sleep_time * 1000);
	if (philo->state == DEAD || philo->state == DONE)
		return ;
	philo->state = THINKING;
}

void	thinking(t_philo *philo)
{
	print_status(philo, "is thinking", false);
	//usleep(philo->eat_time);
	philo->state = FORK;
}

void	eating(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		usleep(1000);
		return ;
	}
	fork_lock(philo);
	philo->last_eat_time = get_time();
	usleep(philo->eat_time * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eat_count--;
	if (!philo->eat_count)
	{
		philo->state = DONE;
		return ;
	}
	philo->state = SLEEPING;
}
