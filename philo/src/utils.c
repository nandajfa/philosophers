/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:50:52 by jefernan          #+#    #+#             */
/*   Updated: 2022/11/14 15:10:16 by jefernan         ###   ########.fr       */
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
			printf("%05li %d has taken a fork\n", time_now, philo->philo_id);
		else if (status == EAT)
			printf ("%05li %d is eating\n", time_now, philo->philo_id);
		else if (status == SLEEP)
			printf("%05li %d is sleeping\n", time_now, philo->philo_id);
		else if (status == THINK)
			printf("%05li %d is thinking\n", time_now, philo->philo_id);
	}
	pthread_mutex_unlock(&(philo->data->write));
}

long int	current_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long int	elapsed_time(long int start_time)
{
	return ((current_time() - start_time));
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
