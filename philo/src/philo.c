/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 03:33:09 by jefernan          #+#    #+#             */
/*   Updated: 2022/11/29 23:04:45 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv))
		return (1);
	init_args(argc, argv, &data);
	init_philos(&data, data.nb_philos);
	create_thread(&data, data.nb_philos);
	clear_mutex(&data);
	free(data.philo);
	free(data.forks);
	return (0);
}

int	create_thread(t_data *data, int nb)
{
	int			i;
	pthread_t	verify;

	i = 0;
	data->start_time = current_time();
	while (i < nb)
	{
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
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		fork_sides[2];		

	philo = arg;
	set_forks(philo, fork_sides);
	if (philo->data->nb_philos == 1)
		one_philo(philo->data);
	if (philo->philo_id % 2 == 0)
		usleep(50);
	while (read_var(&philo->data->died, &philo->data->mutex_died) == 0)
	{
		eat(philo, fork_sides);
		if (philo->data->finish == 1 || is_satisfied(philo->data))
			break ;
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

void	one_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->time_die * 1000);
	printf("%li 1 died\n", elapsed_time(data->start_time));
	write_var(&data->died, &data->mutex_died, 1);
}

void	clear_mutex(t_data *data)
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
}
