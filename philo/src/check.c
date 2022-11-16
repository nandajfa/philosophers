/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 03:33:04 by jefernan          #+#    #+#             */
/*   Updated: 2022/11/03 23:03:56 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
	{
		printf("%s%s\n", ERROR, USAGE);
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_isdigit(argv[i]) || (!ft_atoi(argv[i])))
		{
			printf("%s%s", ERROR_INT, USAGE);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	num;

	i = 0;
	num = 0;
	while (ft_isspace(*str))
		str++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num < 0 || num > INT_MAX)
		return (0);
	return (num);
}

int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			return (1);
		str++;
	}
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}
