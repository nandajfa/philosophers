/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 02:52:50 by jefernan          #+#    #+#             */
/*   Updated: 2022/11/15 01:27:44 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo, int *fork_sides)
{
	hold_forks(philo, fork_sides);
	print_status(philo, EAT);
	write_var(&philo->last_meal, &(philo->mutex_last_meal), current_time());
	usleep(philo->data->time_eat * 1000);
	drop_forks(philo, fork_sides);
}

void	hold_forks(t_philo *philo, int *fork_sides)
{
	pthread_mutex_lock(&philo->data->forks[fork_sides[LEFT_PHILO]]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->data->forks[fork_sides[RIGHT_PHILO]]);
	print_status(philo, FORK);
}

void	drop_forks(t_philo *philo, int *fork_sides)
{
	pthread_mutex_unlock(&philo->data->forks[fork_sides[LEFT_PHILO]]);
	pthread_mutex_unlock(&philo->data->forks[fork_sides[RIGHT_PHILO]]);
	write_var(&philo->nb_ate_meals, &(philo->mutex_ate_meals),
		read_var(&philo->nb_ate_meals, &(philo->mutex_ate_meals)) + 1);
}

void	think(t_philo *philo)
{
	if (philo->data->finish == 0)
		print_status(philo, THINK);
}

void	sleeping(t_philo *philo)
{
	if (philo->data->finish == 0)
	{
		print_status(philo, SLEEP);
		usleep(philo->data->time_sleep * 1000);
	}
}
