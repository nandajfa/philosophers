/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 03:33:09 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/06 23:15:00 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	init_args(argc, argv, &data);
	init_mutex(&data);
	init_philos(&data, data.nb_philos);
	create_thread(&data, data.nb_philos);
	clear_all(&data);
	return (0);
}

void	clear_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&(data->philo)[i].mutex_last_meal);
		pthread_mutex_destroy(&(data->philo)[i].mutex_ate_meals);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->mutex_died);
	pthread_mutex_destroy(&data->mutex_finish);
	free(data->philo);
	free(data->forks);
}
