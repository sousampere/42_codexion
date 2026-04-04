/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 08:39:36 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/04 09:20:07 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	debug_args(t_args*args)
{
	printf("--- DEBUG ARGS ---\n");
	printf("nb_coders: %d\n", args->nb_coders);
	printf("burnout_time: %d\n", args->burnout_time);
	printf("compile_time: %d\n", args->compile_time);
	printf("debug_time: %d\n", args->debug_time);
	printf("refactor_time: %d\n", args->refactor_time);
	printf("nb_compiles: %d\n", args->nb_compiles);
	printf("dongle_cooldown: %d\n", args->dongle_cooldown);
	printf("scheduler: %s\n", args->scheduler);
}
