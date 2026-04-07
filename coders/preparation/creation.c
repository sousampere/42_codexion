/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:51:46 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/07 13:21:16 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	free_all(t_manager *manager)
{
	free(manager->args);
	// MUST IMPLEMENT FREEING DONGLES
	free(manager->coders);
	free(manager);
}

t_coder	*create_coders(t_args *args)
{
	int		i;
	t_coder	*coders;

	coders = malloc(sizeof(t_coder) * args->nb_coders);
	if (!coders)
		return (NULL);
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

t_manager	*create_manager(int argc, char **argv)
{
	t_args 		*args;
	t_coder 	*coders;
	t_manager	*manager;

	args = get_args(argc, argv);
	if (!args)
	{
		printf("Invalid arguments.\n");
		free(args);
		return (NULL);
	}
	coders = create_coders(args);
	if (!coders)
	{
		printf("Failed to allocate memory to create coders.\n");
		return (NULL);
	}
	manager = malloc(sizeof(t_manager));
	if (!manager)
		return (NULL);
	manager->args = args;
	manager->coders = coders;
	return (manager);
}
