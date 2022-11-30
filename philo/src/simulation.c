/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 02:52:50 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/01 00:28:57 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	hold_forks(philo);
	print_status(philo, EAT);
	write_var(&philo->last_meal, &(philo->mutex_last_meal),
		elapsed_time(philo->data->start_time));
	time_sleep(philo->data->time_eat, current_time());
	write_var(&philo->nb_ate_meals, &(philo->mutex_ate_meals),
		read_var(&philo->nb_ate_meals, &(philo->mutex_ate_meals)) + 1);
	drop_forks(philo);
}

void	hold_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	print_status(philo, FORK);
	print_status(philo, FORK);
}

void	drop_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	think(t_philo *philo)
{
	if (read_var(&philo->data->finish, &philo->data->mutex_finish) == 0)
		print_status(philo, THINK);
}

void	sleeping(t_philo *philo)
{
	if (read_var(&philo->data->finish, &philo->data->mutex_finish) == 0)
	{
		print_status(philo, SLEEP);
		time_sleep(philo->data->time_sleep, current_time());
	}
}
