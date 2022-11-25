/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 03:33:09 by jefernan          #+#    #+#             */
/*   Updated: 2022/11/25 23:17:52 by jefernan         ###   ########.fr       */
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
		one_philo(philo, fork_sides);
	if (philo->philo_id % 2 == 0)
		usleep(50);
	while (read_var(&philo->data->died, &philo->data->mutex_died) == 0)
	{
		eat(philo, fork_sides);
		if (read_var(&philo->data->finish, &philo->data->mutex_finish) == 1 
			|| is_satisfied(philo->data))
			break ;
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

void	one_philo(t_philo *philo, int *fork_sides)
{
	pthread_mutex_lock(&philo->data->forks[fork_sides[RIGHT_PHILO]]);
	printf("%05li %d has taken a fork\n", elapsed_time(philo->data->start_time),
		philo->philo_id);
	pthread_mutex_unlock(&philo->data->forks[fork_sides[RIGHT_PHILO]]);
	usleep(philo->data->time_die * 1000);
	pthread_mutex_lock(&(philo->data->write));
	printf("%05li %d died\n", elapsed_time(philo->data->start_time),
		philo->philo_id);
	pthread_mutex_unlock(&(philo->data->write));
	write_var(&philo->data->died, &philo->data->mutex_died, 1);
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
