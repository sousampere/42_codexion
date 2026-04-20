/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:28:17 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 17:50:12 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	compile(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 2);
	pthread_mutex_lock(&mng->gobal_mtx);
	coder->burnout_delay = get_rel_time(mng) + mng->arg->burnout_time;
	pthread_mutex_unlock(&mng->gobal_mtx);
	usleep(mng->arg->compile_time * 1000);
	pthread_mutex_lock(&mng->gobal_mtx);
	coder->left_dongle->cooldown_end = get_rel_time(mng) + mng->arg->dongle_cooldown;
	coder->nb_compiles += 1;
	pthread_mutex_unlock(&mng->gobal_mtx);
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

void	pickup_dongle(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 1);
}
