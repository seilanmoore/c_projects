/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 22:52:23 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/26 23:43:48 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define TRUE 1
# define FALSE 0
# define ERROR -1
# define SUCCESS 0
# define INVALID "invalid argument"
# define USAGE "usage: ./philo "
# define ARGS "number_of_philosophers time_to_die time_to_eat time_to_sleep "
# define OPTIONAL "[number_of_times_each_philosopher_must_eat]"
# define PHILO "philo: "
# define ECREATE "pthread_create: could not create thread"
# define EJOIN "pthread_join: could not join thread"
# define EALLOC "malloc: could not alocate memory"
# define EGETTIME "gettimeofday: could not set time"
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

typedef struct timeval	t_timeval;

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		t1;
	int				id;
	int				eat_count;
	int				status;
	int				eating;
	time_t			time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	int				philo_num;
	int				must_eat;
	int				finished;
	int				dead;
	t_philo			*philo;
	time_t			death_time;
	time_t			eat_time;
	time_t			sleep_time;
	time_t			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(char *str);
int		ft_atoi(const char *str);
int		ft_strcmp(char *str1, char *str2);
void	ft_usleep(time_t ms);
time_t	get_time(void);
int		ft_error(void *data, char *message, void *aux);
void	ft_clear(t_data *data);
void	clear_one(t_data *data);
int		check_args(int argc, char **argv);
int		init(t_data *data, char **argv, int argc);
int		case_one(t_data *data);
int		simulation(t_data *data);
void	logs(char *log, t_philo *philo);
void	eat(t_philo *philo);

#endif