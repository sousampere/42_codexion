/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:54:51 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/10 09:07:55 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	release_dongles(t_coder *coder, t_manager *mng)
{
	coder->left_dongle->cooldown = get_rel_time(mng)
		+ mng->args->dongle_cooldown;
	coder->right_dongle->cooldown = get_rel_time(mng)
		+ mng->args->dongle_cooldown;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	coder->left_dongle->is_in_use = 0;
	coder->right_dongle->is_in_use = 0;
}

void	compile(t_coder *coder, t_manager *mng)
{
	printf("%ld %d is compiling\n", get_rel_time(mng), coder->coder_id);
	coder->time_to_burnout = get_rel_time(mng) + mng->args->burnout_time;
	usleep(mng->args->compile_time * 1000);
	coder->nb_compiles += 1;
	release_dongles(coder, mng);
}

void	refactor(t_coder *coder, t_manager *mng)
{
	printf("%ld %d is refactoring\n", get_rel_time(mng), coder->coder_id);
	usleep(mng->args->refactor_time * 1000);
}

void	take_dongles(t_coder *coder, t_manager *mng)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	coder->left_dongle->is_in_use = 1;
	coder->right_dongle->is_in_use = 1;
	printf("%ld %d has taken a dongle\n", get_rel_time(mng), coder->coder_id);
	printf("%ld %d has taken a dongle\n", get_rel_time(mng), coder->coder_id);
}

void	wait_for_dongles(t_coder *coder, t_manager *mng)
{
	while (1)
	{
		if (coder->left_dongle->is_in_use == 0
			&& coder->right_dongle->is_in_use == 0
			&& (long)coder->left_dongle->cooldown >= get_rel_time(mng)
			&& (long)coder->right_dongle->cooldown >= get_rel_time(mng))
		{
			take_dongles(coder, mng);
			return ;
		}
	}
	return ;
}
