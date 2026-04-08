/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:19:28 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/08 10:35:56 by gaspard          ###   ########.fr       */
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

typedef struct s_dongle	t_dongle; // Pre-declaration
typedef struct s_coder	t_coder; // Pre-declaration

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
	pthread_cond_t	condition; // wait on that condition to broadcast
	int				is_in_use; // 1 if a coder is using it
	t_coder			*heap[2];
}	t_dongle;

typedef struct s_manager
{
	t_coder		*coders; // list of (nb_coders) coders
	t_args		*args; // pointer to args struct
}	t_manager;


// Preparation
t_args		*get_args(int argc, char **argv);
t_coder		*create_coders(t_args *args);
void		give_dongles(t_manager *mng);
void		free_all(t_manager *manager);
t_manager	*create_manager(int argc, char **argv);

// Misc
void		*ft_calloc(size_t nmemb, size_t size);
long		get_time_in_ms(void);
void		debug_args(t_args *args);

// Simulation
int			start_simulation(t_manager *mng);
void		*routine(void *coder);
void		pick_dongle(t_coder *coder);


#endif // !CODEXION_H
