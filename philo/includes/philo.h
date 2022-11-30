/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jefernan <jefernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:53:53 by jefernan          #+#    #+#             */
/*   Updated: 2022/12/01 00:47:17 by jefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> // threads
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <sys/time.h> // gettimeofday
# include <unistd.h> // usleep

# define INT_MAX 2147483647

# define EAT 1
# define THINK 2
# define SLEEP 3
# define FORK 4

/*Errors message*/
# define ERROR "Error: Wrong number of arguments.\n"
# define ERROR_INT "Error: Arguments must be numbers and greater than 0.\n"
# define USAGE "Use: NB_OF_PHILOS  TIME_TO_DIE  TIME_TO_EAT  TIME_TO_SLEEP \
[NB_TIMES_MUST_EAT](Optional)\n"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_times_must_eat;
	int				available;
	long int		start_time;
	long int		finish;
	long int		died;
	pthread_mutex_t	write;
	pthread_mutex_t	mutex_finish;
	pthread_mutex_t	mutex_died;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

struct s_philo
{
	int				philo_id;
	long int		nb_ate_meals;
	long int		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mutex_last_meal;
	pthread_mutex_t	mutex_ate_meals;
	pthread_t		thread;
	t_data			*data;
};

// philo
int			create_thread(t_data *data, int nb);
void		*routine(void *arg);
void		one_philo(t_data *data);
void		clear_mutex(t_data *data);

// check 
int			check_args(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_isdigit(char *str);
int			ft_isspace(int c);

// init
void		init_args(int argc, char **argv, t_data *data);
void		init_philos(t_data *data, int nb);
void		init_mutex(t_data *data);

// simulation
void		eat(t_philo *philo);
void		think(t_philo *philo);
void		sleeping(t_philo *philo);
void		hold_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

// verify
void		*check_philos(void	*arg);
int			verify_death(t_data *data);
int			is_satisfied(t_data *data);
void		somebody_died(t_data *data, int i);

// utils
void		print_status(t_philo *philo, int status);
long int	read_var(long int *var, pthread_mutex_t *mutex);
void		write_var(long int *var, pthread_mutex_t *mutex, long int status);

// time
long int	current_time(void);
long int	elapsed_time(long int start_time);
void		time_sleep(long int waiting, long int time);

#endif