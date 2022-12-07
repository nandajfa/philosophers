/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 19:41:41 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/07 14:27:30 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_data *data, int nb)
{
	int			i;
	pthread_t	verify;

	i = 0;
	data->start_time = get_time_ms();
	while (i < nb)
	{
		data->philo[i].last_meal = data->start_time;
		pthread_create(&data->philo[i].thread, NULL, &routine,
			&data->philo[i]);
		i++;
	}
	pthread_create(&verify, NULL, &check_philos, data);
	i = 0;
	while (i < nb)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(verify, NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;	

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
		return (one_philo(philo->data));
	if (philo->philo_id % 2 == 0)
		usleep(300);
	while (philo->nb_ate_meals < philo->data->nb_times_must_eat
		&& read_var(&philo->data->died, &philo->data->mutex_died) == 0)
	{
		eat(philo);
		if (read_var(&philo->data->finish, &philo->data->mutex_finish) == 1)
			break ;
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

void	*one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->time_die * 1000);
	printf("%li 1 died\n", current_time(data->start_time));
	write_var(&data->died, &data->mutex_died, 1);
	return (NULL);
}
