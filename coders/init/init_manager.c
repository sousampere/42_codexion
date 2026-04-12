/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 11:52:20 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/12 14:49:06 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

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
	long			current_time;

	i = 0;
	mng->dongles = malloc(mng->args->nb_coders * sizeof(t_dongle));
	if (!mng->dongles)
		return ;
	current_time = get_rel_time(mng);
	while (i < mng->args->nb_coders - 1)
	{
		mng->dongles[i].cooldown = current_time;
		mng->dongles[i].dongle_id = i + 1;
		mng->coders[i].left_dongle = &mng->dongles[i];
		mng->coders[i].right_dongle = &mng->dongles[i + 1];
		pthread_mutex_init(&mng->dongles[i].mutex, NULL);
		i++;
	}
	// mng->dongles[i].cooldown = current_time;
	mng->dongles[i].dongle_id = i + 1;
	mng->coders[i].left_dongle = &mng->dongles[i];
	mng->coders[i].right_dongle = &mng->dongles[0];
	pthread_mutex_init(&mng->dongles[i].mutex, NULL);
}

t_manager	*create_manager(int argc, char **argv)
{
	t_args		*args;
	t_coder		*coders;
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
	pthread_mutex_init(&manager->print_mutex, NULL);
	return (manager);
}
