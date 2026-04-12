/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:19:28 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/12 14:44:05 by gaspard          ###   ########.fr       */
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
	char	*scheduler; // fifo or edf
}	t_args;

typedef struct s_coder
{
	int			coder_id;
	int			time_to_burnout;
	int			nb_compiles;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
}	t_coder;

typedef struct s_dongle
{
	long			cooldown; // time in ms of last use
	int				dongle_id; // id of the dongle
	pthread_mutex_t	mutex; // lock/unlock the right to use it
	int				is_in_use; // 1 if a coder is using it
	t_coder			*heap[2];
}	t_dongle;

typedef struct s_manager
{
	t_coder			*coders; // list of (nb_coders) coders
	t_dongle		*dongles; // list of dongles
	t_args			*args; // pointer to args struct
	pthread_mutex_t	print_mutex;
	long			start_timestamp; // timestamp of simulation start
}	t_manager;

typedef struct s_routine_arg
{
	t_coder		*coder;
	t_manager	*manager;
}	t_routine_arg;

// init
t_args		*get_args(int argc, char **argv);
t_manager	*create_manager(int argc, char **argv);

// time
long		get_time_in_ms(void);
long		get_rel_time(t_manager *mng);

#endif // !CODEXION_H
