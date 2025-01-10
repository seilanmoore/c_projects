/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 21:29:09 by smoore-a          #+#    #+#             */
/*   Updated: 2025/01/10 12:32:32 by smoore-a         ###   ########.fr       */
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
# include <limits.h>

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

typedef enum e_exit_code
{
	ERROR = 1,
	E_INFO,
	E_TIME,
	E_THREAD_CREATE,
	E_MUTEX_LOCK,
	E_MUTEX_UNLOCK,
	E_MUTEX_DESTROY
}	t_exit_code;

typedef enum e_state
{
	THINK,
	FORK,
	EAT,
	SLEEP,
	DIE
}	t_state;

typedef pthread_mutex_t	t_mutex;

typedef struct timeval	t_timeval;

typedef struct s_data	t_data;

typedef struct s_fork
{
	t_mutex		fork;
	int			fork_id;
}	t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	int			id;
	int			n_meal;
	bool		full;
	bool		eating;
	time_t		last_meal;
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_mutex		philo_mutex;
	t_data		*data;
}	t_philo;

typedef struct s_info
{
	int		n_philo;
	time_t	die_t;
	time_t	eat_t;
	time_t	sleep_t;
	int		n_meal;
}	t_info;

typedef struct s_data
{
	t_info		info;
	t_philo		*philo;
	t_fork		*fork;
	pthread_t	monitor;
	int			n_threads_running;
	time_t		start_time;
	bool		threads_ready;
	bool		started;
	bool		ended;
	t_mutex		data_mutex;
	t_mutex		print_mutex;
	int			e_code;
}	t_data;

// check_info //
int		check_info(t_data *data, int argc, char **argv);

// init //
int		init(t_data *data);

// simulation //
void	*simulation(void *philo_);
void	start_simulation(t_data *data);

// action //
void	eat(t_philo *philo);

// logs //
void	logs(t_philo *philo, t_state state);

// monitor //
void	*monitor(void *philo_);

// time //
time_t	get_time(void);
void	ft_usleep(time_t usec, t_data *data);

// error //
int		print_msg(char *msg, int code);

// cleanup //
void	cleanup(t_data *data);

// get_set_value //
void	set_bool(t_mutex *mutex, bool *var, bool value);
bool	get_bool(t_mutex *mutex, bool *var);
void	set_long(t_mutex *mutex, long *var, long value);
long	get_long(t_mutex *mutex, long *var);
bool	simulation_ended(t_data *data);

// sync_utils //
bool	all_threads_running(t_mutex *mutex, int *n_thread, int n_philo);
void	increase_running_threads(t_mutex *mutex, int *value);
void	sync_threads(t_data *data);

// utils_1 //
long	ft_atol(const char *str);

// utils_2 //
int		ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
//void	reassign_forks(t_mutex **fork_x, t_mutex **fork_y, t_philo *philo);

#endif
