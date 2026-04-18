/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:28:17 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 17:28:31 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	compile(t_coder *coder, t_manager *mng)
{
	coder->left_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	coder->right_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	sprint(coder, mng, 2);
	coder->burnout_delay = get_rel_time(mng) + mng->arg->burnout_time;
	usleep(mng->arg->compile_time * 1000);
	coder->nb_compiles += 1;
}

void	debug(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 4);
	usleep(mng->arg->compile_time * 1000);
}

void	refactor(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 3);
	usleep(mng->arg->refactor_time * 1000);
}
