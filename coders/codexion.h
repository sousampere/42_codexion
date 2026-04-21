/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:19:28 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 17:41:41 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_dongle			t_dongle; // Pre-declaration
typedef struct s_coder			t_coder; // Pre-declaration
typedef struct s_routine_arg	t_routine_arg; // Pre-declaration

typedef struct s_args
{
	int		nb_coders;
	int		burnout_time; // in ms
	int		compile_time; // in ms
	int		debug_time; // in ms
	int		refactor_time; // in ms
	int		nb_compiles;
	int		dongle_cooldown; // in ms
	bool	scheduler; // 0 = edf, 1 = fifo
}	t_args;

typedef struct s_coder
{
	int			id;
	int			burnout_delay;
	int			nb_compiles;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
}	t_coder;

typedef struct s_dongle
{
	int				id;
	int				cooldown_end;
	t_coder			*heap[2];
	pthread_mutex_t	mtx_heap;
	pthread_mutex_t	mutex;
	bool			is_used;
}	t_dongle;

typedef struct s_manager
{
	t_args			*arg;
	t_coder			*coders;
	bool			is_ended;
	long			start_timestamp;
	pthread_mutex_t	printf_mtx;
	pthread_t		*coders_threads;
	t_dongle		*dongles;
	t_routine_arg	*routine_args;
	pthread_mutex_t	gobal_mtx;
	pthread_mutex_t	rel_time_mtx;
}	t_manager;

typedef struct s_routine_arg
{
	t_coder		*coder;
	t_manager	*manager;
}	t_routine_arg;

// free
void		*free_mng_and_args(t_manager *mng);
void		free_all(t_manager *mng);

// manager
t_manager	*init_manager(int argc, char **argv);
t_args		*get_args(int argc, char **argv);

// heap
void		init_heap(t_dongle *dongle);
void		heap_push(t_dongle *dongle, t_coder *coder, t_manager *mng);
void		heap_pop(t_dongle *dongle);
bool		has_heap_priority(t_dongle *dongle, t_coder *coder);
void		heap_rm(t_dongle *dongle, t_coder *coder);
bool		will_deadlock(t_manager *mng);

// monitor
void		start_monitor(t_manager *mng);
bool		check_burnout(t_manager *mng);
bool		check_end(t_manager *mng);

// time
long		get_time_in_ms(void);
int			get_rel_time(t_manager *mng);
void		psleep(long long usec);

// printf_secure
void		sprint(t_coder *coder, t_manager *mng, int code);

// simulation
void		compile(t_coder *coder, t_manager *mng);
void		debug(t_coder *coder, t_manager *mng);
void		refactor(t_coder *coder, t_manager *mng);
void		start_simulation(t_manager *mng);
void		pickup_dongle(t_coder *coder, t_manager *mng);

// misc
bool		is_ended(t_manager *mng);
void		lock_dongles(t_coder *coder);
void		unlock_dongles(t_coder *coder);
int			has_enough_compiles(t_coder *coder, t_manager *mng);
int			get_burnout(t_manager *mng, t_coder *coder);
void		*ft_calloc(size_t nmemb, size_t size);

#endif // !CODEXION_H