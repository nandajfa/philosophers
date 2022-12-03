/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 00:43:36 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/03 23:59:29 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	time_sleep(long int waiting, long int time)
{	
	while ((current_time() - time) < waiting)
		usleep (40);
}
