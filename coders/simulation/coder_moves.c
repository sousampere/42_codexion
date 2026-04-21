/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:28:17 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/21 12:36:57 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	compile(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 2);
	pthread_mutex_lock(&mng->gobal_mtx);
	coder->burnout_delay = get_rel_time(mng) + mng->arg->burnout_time;
	pthread_mutex_unlock(&mng->gobal_mtx);
	psleep(mng->arg->compile_time * 1000);
	pthread_mutex_lock(&mng->gobal_mtx);
	coder->nb_compiles += 1;
	pthread_mutex_unlock(&mng->gobal_mtx);
}

void	debug(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 4);
	psleep(mng->arg->debug_time * 1000);
}

void	refactor(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 3);
	psleep(mng->arg->refactor_time * 1000);
}

void	pickup_dongle(t_coder *coder, t_manager *mng)
{
	sprint(coder, mng, 1);
}
