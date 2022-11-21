/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:25:31 by jefernan          #+#    #+#             */
/*   Updated: 2022/11/20 23:52:13 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_philos(void	*arg)
{
	t_data	*data;

	data = arg;
	while (!verify_death(data) && !is_satisfied(data))
		continue ;
	return (NULL);
}

int	verify_death(t_data *data)
{
	int			i;
	long int	time_now;

	i = 0;
	if (data->died == 1 || data->finish == 1)
		return (1);
	time_now = elapsed_time(data->start_time);
	while (i < data->nb_philos && data->nb_philos != 1)
	{
		if (time_now - read_var(&(data->philo)[i].last_meal,
			&(data->philo)[i].mutex_last_meal) > data->time_die)
		{
			somebody_died(data, i);
			return (1);
		}
		i++;
		usleep(200);
	}
	if (i >= data->nb_philos)
		i = 0;
	return (0);
}

int	is_satisfied(t_data *data)
{
	int	i;
	int	philo_ate;

	i = 0;
	philo_ate = 0;
	if (data->nb_times_must_eat > 0)
	{
		while (i < data->nb_philos)
		{
			if (read_var(&(data->philo)[i].nb_ate_meals,
				&(data->philo)[i].mutex_ate_meals) >= data->nb_times_must_eat)
			philo_ate++;
			i++;
		}
		if (philo_ate == data->nb_philos)
			return (1);
		else
			return (0);
	}
	return (0);
}

void	somebody_died(t_data *data, int i)
{
	long int	time;

	write_var(&data->died, (&(data->mutex_died)), 1);
	time = elapsed_time(data->start_time);
	pthread_mutex_lock(&(data->write));
	printf("%05ld %d died\n", time, data->philo[i].philo_id);
	pthread_mutex_unlock(&(data->write));
	write_var(&data->finish, (&(data->mutex_finish)), 1);
}