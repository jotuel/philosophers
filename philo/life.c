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
	t_philo	*philo;
	philo = (t_philo *)arg;
	while (!*philo[0].death && philo[0].state) {
		for (int i = 0; philo[i].id; i++) {
			if (get_time() - philo[i].last_eat_time > philo[i].lifetime && philo[i].state) {
			    if (!*philo->death)
					philo[i].state = DEAD;
				*philo[i].death = true;
				print_status(&philo[i], "died", false);
				philo[i].state = DONE;
			}
        }
		usleep(1000);
	}
	return (NULL);
}

void	*philosopher(void *state)
{
	t_philo	*philo;

	philo = state;
	if (philo->id % 2) {
		philo->group = true;
		usleep(philo->eat_time * 1000);
	}
	while (!*philo->begin)
		usleep(1000);
	philo->last_eat_time = *philo->start;
	while (!*philo->death) {
	    switch (philo->state) {
			case FORK:
			    eating(philo);
				break;
			case SLEEPING:
			    sleeping(philo);
				break;
			case THINKING:
			    thinking(philo);
				break;
			default:
			    return (NULL);
		}
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
	usleep(philo->eat_time * 1000);
	philo->state = FORK;
}

void	eating(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork) {
		usleep(1000);
		return ;
	}
	fork_lock(philo);
	philo->last_eat_time = get_time();
	usleep(philo->eat_time * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eat_count--;
	if (!philo->eat_count) {
		philo->state = DONE;
		return ;
	}
	philo->state = SLEEPING;
}
