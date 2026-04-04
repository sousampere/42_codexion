/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 05:42:19 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/04 10:49:14 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*create_coders(t_args *args)
{
	int		i;
	t_coder	*coders;

	coders = malloc(sizeof(t_coder) * args->nb_coders);
	i = 1;
	while (i <= args->nb_coders)
	{
		coders[i - 1].coder_id = i;
		coders[i - 1].time_to_burnout = args->burnout_time;
		coders[i - 1].nb_compiles = 0;
		i++;
	}
	return (coders);
}

int	main(int argc, char **argv)
{
	t_args	*args;
	t_coder	*coders;

	args = get_args(argc, argv);
	if (!args)
		return (printf("Invalid arguments.\n"), 1);
	coders = create_coders(args);
	if (!coders)
		return (printf("Failed to allocate memory.\n"), 1);
}
