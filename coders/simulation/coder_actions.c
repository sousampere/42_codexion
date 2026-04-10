/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:54:51 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/10 18:35:40 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	release_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	coder->left_dongle->is_in_use = 0;
	coder->right_dongle->is_in_use = 0;
}

void	compile(t_coder *coder, t_manager *mng)
{
	coder->left_dongle->cooldown = get_rel_time(mng)
		+ mng->args->dongle_cooldown;
	coder->right_dongle->cooldown = get_rel_time(mng)
		+ mng->args->dongle_cooldown;
	print(coder, mng, 2);
	coder->time_to_burnout = get_rel_time(mng) + mng->args->burnout_time;
	usleep(mng->args->compile_time * 1000);
	coder->nb_compiles += 1;
	release_dongles(coder);
}

void	debug(t_coder *coder, t_manager *mng)
{
	print(coder, mng, 4);
	usleep(mng->args->compile_time * 1000);
}

void	refactor(t_coder *coder, t_manager *mng)
{
	printf("Printting refactor\n");
	print(coder, mng, 3);
	printf("Printed refactor\n");
	usleep(mng->args->refactor_time * 1000);
	printf("slept\n");
}

void	take_dongles(t_coder *coder, t_manager *mng)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	coder->left_dongle->is_in_use = 1;
	coder->right_dongle->is_in_use = 1;
	print(coder, mng, 1);
}

void	wait_for_dongles(t_coder *coder, t_manager *mng)
{
	while (1)
	{
		// printf("%d %d %ld %ld %ld \n",
		// 	coder->left_dongle->is_in_use,
		// 	coder->right_dongle->is_in_use,
		// 	(long)coder->left_dongle->cooldown,
		// 	(long)coder->right_dongle->cooldown,
		// 	get_rel_time(mng));
		
		
		if (coder->left_dongle->is_in_use == 0
			&& coder->right_dongle->is_in_use == 0
			&& (long)coder->left_dongle->cooldown <= get_rel_time(mng)
			&& (long)coder->right_dongle->cooldown <= get_rel_time(mng))
		{
			printf("Took dongles for comp %d\n", coder->nb_compiles);
			take_dongles(coder, mng);
			return ;
		}
	}
	return ;
}
