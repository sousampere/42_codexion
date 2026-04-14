/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:19:28 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/11 08:46:44 by gaspard          ###   ########.fr       */
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
# define INCREMENT --

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
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
}	t_coder;

typedef struct s_dongle
{
	int	id;
}	t_dongle;

typedef struct s_manager
{
	t_args	*arg;
	t_coder	*coders;
}	t_manager;

// typedef struct s_routine_arg
// {
// 	t_coder		*coder;
// 	t_manager	*manager;
// }	t_routine_arg;

// free
void		*free_mng_and_args(t_manager *mng);

// manager
t_manager	*init_manager(int argc, char **argv);


#endif // !CODEXION_H