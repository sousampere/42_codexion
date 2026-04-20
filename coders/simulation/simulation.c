/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:27:29 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 18:50:32 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	release_dongles(t_coder *coder, t_manager *mng)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	coder->left_dongle->is_used = false;
	coder->left_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	coder->right_dongle->is_used = false;
	coder->right_dongle->cooldown_end = get_rel_time(mng)
		+ mng->arg->dongle_cooldown;
	pthread_mutex_unlock(&coder->right_dongle->mutex);
}

void	*routine(void *arg)
{
	t_routine_arg	*args;

	args = (t_routine_arg *) arg;
	while (args->coder->nb_compiles < args->manager->arg->nb_compiles
		&& !args->manager->is_ended)
	{
		if (args->manager->arg->nb_coders == 1)
			return (NULL);
		// routine
	}
	return (NULL);
}

void	start_simulation(t_manager *mng)
{
	int				i;

	i = -1;
	mng->coders_threads = malloc(sizeof(pthread_t) * mng->arg->nb_coders);
	mng->routine_args = malloc(sizeof(t_routine_arg) * mng->arg->nb_coders);
	while (++i < mng->arg->nb_coders)
	{
		mng->routine_args[i].manager = mng;
		mng->routine_args[i].coder = &mng->coders[i];
		pthread_create(&mng->coders_threads[i],
			NULL, &routine, &mng->routine_args[i]);
	}
}
