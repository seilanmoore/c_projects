/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:39:26 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/30 12:35:09 by smoore-a         ###   ########.fr       */
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
# include <curses.h>

# define NL "\n"
# define PRO "Prototype: "
# define EXE "./philo "
# define ARGS "number_of_philosophers time_to_die time_to_eat time_to_sleep "
# define OPT "[number_of_times_each_philosopher_must_eat]"
# define E_ARG "Error: invalid number of arguments. "
# define E_ARG_N_PHILO "Error: number_of_philosophers (<= 0 OR > 200)"
# define E_ARG_DIE_TIME "Error: time_to_die < 60"
# define E_ARG_EAT_TIME "Error: time_to_eat < 60"
# define E_ARG_SLEEP_TIME "Error: time_to_sleep < 60"
# define E_ARG_N_MEALS "Error: number_of_meals < 0"
# define E_GET_TIME "Error: couldn't get time"

enum e_exit_code
{
	ERROR = 1,
	E_INFO,
	E_TIME,
	E_MUTEX_INIT,
	E_THREAD_CREATE
};

enum e_state
{
	THINK = 0,
	FORK,
	EAT,
	SLEEP,
	DIE
};

typedef pthread_mutex_t	t_t_mutex;

typedef struct timeval	t_timeval;

typedef struct s_data	t_data;

typedef struct s_mutex
{
	int			to_destroy;
	t_t_mutex	lock;
}	t_mutex;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			n_meal;
	int			last_meal;
	t_mutex		*r_fork;
	t_mutex		*l_fork;
	t_data		*data;
}	t_philo;

typedef struct s_info
{
	int	n_philo;
	int	die_t;
	int	eat_t;
	int	sleep_t;
	int	n_meal;
}	t_info;

typedef struct s_data
{
	t_philo		*philo;
	t_info		info;
	t_mutex		*fork;
	int			start_time;
	bool		dead;
	t_mutex		print_m;
	t_mutex		die_t_m;
	t_mutex		n_meal_m;
	t_mutex		state_m;
	t_mutex		err_code_m;
	int			e_code;
}	t_data;

// check_info //
int		check_info(t_data *data, int argc, char **argv);

// init //
int		init(t_data *data);

// routine //
void	*routine(void *data);
void	*monitor(void *data_);

// action //
void	logs(t_philo *philo, int state, time_t time);
void	take_fork(t_philo *philo);

// time //
time_t	get_time(void);
void	ft_usleep(time_t time);

// error //
int		print_msg(char *msg, int code);

// cleanup //
void	cleanup(t_data *data);

// utils //
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);

#endif