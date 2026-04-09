/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:47:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/09 12:46:45 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// void	update_dongles_cooldown(t_coder *coder, t_manager *manager)
// {
	
// }

void	compile(t_coder *coder, t_manager *mng)
{
	// update burnout deadline
	coder->time_to_burnout = get_rel_time(mng) + mng->args->burnout_time;
	usleep(mng->args->compile_time * 1000); // Simulate compilation
	coder->nb_compiles += 1; // update compilation counter
}

void	start_simulation(t_manager *mng)
{
	
}