/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:43:36 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/06 15:44:34 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time_ms(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000000 + tv.tv_usec) / 1000;
	return (time);
}

long int	current_time(long int start_time)
{
	return ((get_time_ms() - start_time));
}

void	time_sleep(long int waiting, long int time)
{	
	while ((get_time_ms() - time) < waiting)
		usleep (40);
}
