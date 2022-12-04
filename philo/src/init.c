/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:28:08 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/04 23:19:00 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(int argc, char **argv, t_data *data)
{
	if (argc == 5 || argc == 6)
	{
		data->nb_philos = ft_atoi(argv[1]);
		data->time_die = ft_atoi(argv[2]);
		data->time_eat = ft_atoi(argv[3]);
		data->time_sleep = ft_atoi(argv[4]);
		data->start_time = 0;
		data->finish = 0;
		data->died = 0;
		if (argc == 6)
			data->nb_times_must_eat = ft_atoi(argv[5]);
		else
			data->nb_times_must_eat = -1;
	}
}

void	init_mutex(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->mutex_died, NULL);
	pthread_mutex_init(&data->mutex_finish, NULL);
	data->forks = malloc(data->nb_philos * sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_data *data, int nb)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(nb * sizeof(t_philo));
	while (i < nb)
	{
		pthread_mutex_init(&philo[i].mutex_last_meal, NULL);
		pthread_mutex_init(&philo[i].mutex_ate_meals, NULL);
		philo[i].philo_id = i + 1;
		philo[i].right_fork = &data->forks[i];
		philo[i].left_fork = &data->forks[i + 1];
		philo[i].data = data;
		philo[i].nb_ate_meals = 0;
		philo[i].last_meal = 0;
		i++;
	}
	philo[i - 1].left_fork = &data->forks[0];
	data->philo = philo;
}
