/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 02:52:50 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/04 23:17:16 by jefernan         ###   ########.fr       */
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
	drop_forks(philo);
}

void	hold_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, FORK);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, FORK);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	write_var(&philo->nb_ate_meals, &(philo->mutex_ate_meals),
		read_var(&philo->nb_ate_meals, &(philo->mutex_ate_meals)) + 1);
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
