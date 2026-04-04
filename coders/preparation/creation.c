/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:51:46 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/04 19:52:14 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	give_dongles(t_coder *coders, t_args *args)
{
	int				i;
	t_dongle		*dongles;
	long			current_time;

	i = 0;
	dongles = ft_calloc(args->nb_coders, sizeof(t_dongle)); // Create n dongles memory place
	current_time = get_time_in_ms();
	while (i < args->nb_coders - 1)
	{
		dongles[i].cooldown = current_time;
		dongles[i].dongle_id = i + 1;
		coders[i].left_dongle = &dongles[i];
		coders[i].right_dongle = &dongles[i + 1];
		i++;
	}
	dongles[i].cooldown = current_time;
	dongles[i].dongle_id = i + 1;
	coders[i].left_dongle = &dongles[i];
	coders[i].right_dongle = &dongles[0];
}

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