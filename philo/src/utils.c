/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:50:52 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/01 00:46:02 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, int status)
{
	long int	time_now;

	pthread_mutex_lock(&(philo->data->write));
	time_now = elapsed_time(philo->data->start_time);
	if (read_var(&philo->data->finish, &philo->data->mutex_finish) == 0)
	{
		if (status == FORK)
			printf("%ld %d has taken a fork\n", time_now, philo->philo_id);
		else if (status == EAT)
			printf ("%ld %d is eating\n", time_now, philo->philo_id);
		else if (status == SLEEP)
			printf("%ld %d is sleeping\n", time_now, philo->philo_id);
		else if (status == THINK)
			printf("%ld %d is thinking\n", time_now, philo->philo_id);
	}
	pthread_mutex_unlock(&(philo->data->write));
}

long int	read_var(long int *var, pthread_mutex_t *mutex)
{
	long int	temp;

	pthread_mutex_lock(mutex);
	temp = *var;
	pthread_mutex_unlock(mutex);
	return (temp);
}

void	write_var(long int *var, pthread_mutex_t *mutex, long int status)
{
	pthread_mutex_lock(mutex);
	*var = status;
	pthread_mutex_unlock(mutex);
}
