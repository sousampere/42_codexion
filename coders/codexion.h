/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:19:28 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/03 08:23:02 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

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

t_args	*get_args(int argc, char **argv);

#endif // !CODEXION_H
