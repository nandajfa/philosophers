/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 09:28:08 by jefernan          #+#    #+#             */
/*   Updated: 2022/11/22 16:05:25 by jefernan         ###   ########.fr       */
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

void	init_philos(t_data *data, int nb)
{
	int		i;
	t_philo	*philo;

	i = 0;
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->mutex_died, NULL);
	pthread_mutex_init(&data->mutex_finish, NULL);
	philo = malloc((data->nb_philos + 1) * sizeof(t_philo));
	data->forks = malloc((nb + 1) * sizeof(pthread_mutex_t));
	while (i <= nb)
	{
		philo[i].philo_id = i + 1;
		philo[i].ph_index = i;
		philo[i].data = data;
		philo[i].nb_ate_meals = 0;
		philo[i].last_meal = 0;
		pthread_mutex_init(&philo[i].mutex_last_meal, NULL);
		pthread_mutex_init(&philo[i].mutex_ate_meals, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->philo = philo;
}

void	set_forks(t_philo *philo, int *fork_sides)
{
//	if (philo->data->nb_philos == 2)
//	{
//		fork_sides[LEFT_PHILO] = 0;
//		fork_sides[RIGHT_PHILO] = 1;
//		return ;
//	}
	fork_sides[LEFT_PHILO] = philo->ph_index;
	if (philo->ph_index == 0)
		fork_sides[RIGHT_PHILO] = philo->data->nb_philos - 1;
	else
		fork_sides[RIGHT_PHILO] = philo->ph_index - 1;
}

