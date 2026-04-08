/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:51:46 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/08 11:41:30 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	free_all(t_manager *manager)
{
	int	i;
	
	i = -1;
	while (++i < manager->args->nb_coders)
		pthread_mutex_destroy(&manager->coders[i].left_dongle->mutex);
	// MUST IMPLEMENT FREEING DONGLES
	free(manager->coders);
	free(manager->args);
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

void	give_dongles(t_manager *mng)
{
	int				i;
	t_dongle		*dongles;
	long			current_time;

	i = 0;
	// Create n dongles memory place
	dongles = ft_calloc(mng->args->nb_coders, sizeof(t_dongle));
	if (!dongles)
		return ;
	current_time = get_time_in_ms();
	while (i < mng->args->nb_coders - 1)
	{
		dongles[i].cooldown = current_time;
		dongles[i].dongle_id = i + 1;
		mng->coders[i].left_dongle = &dongles[i];
		mng->coders[i].right_dongle = &dongles[i + 1];
		pthread_mutex_init(&dongles[i].mutex, NULL);
		i++;
	}
	dongles[i].cooldown = current_time;
	dongles[i].dongle_id = i + 1;
	mng->coders[i].left_dongle = &dongles[i];
	mng->coders[i].right_dongle = &dongles[0];
	pthread_mutex_init(&dongles[i].mutex, NULL);
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
	manager->start_timestamp = get_time_in_ms();
	give_dongles(manager);
	return (manager);
}
