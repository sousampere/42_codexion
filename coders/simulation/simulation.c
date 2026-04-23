/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:27:29 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/21 17:41:10 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

// ----- Verifications



void	pickup_dongles(t_coder *coder, t_manager *mng)
{
	while (!is_ended(mng))
	{
		lock_dongles(coder);
		if (!coder->left_dongle->is_used
			&& !coder->right_dongle->is_used
			&& has_heap_priority(coder->left_dongle, coder)
			&& has_heap_priority(coder->right_dongle, coder)
			&& coder->left_dongle->cooldown_end <= get_rel_time(mng)
			&& coder->right_dongle->cooldown_end <= get_rel_time(mng)
			// && coder->nb_compiles >= mng->coders[(coder->id + 1) % mng->arg->nb_coders].nb_compiles
		)
		{
			sprint(coder, mng, 1);
			sprint(coder, mng, 1);
			coder->right_dongle->is_used = 1;
			coder->left_dongle->is_used = 1;
			heap_pop(coder->left_dongle);
			heap_pop(coder->right_dongle);
			unlock_dongles(coder);
			return ;
		}
		unlock_dongles(coder);
		psleep(1000);
	}
}


void	release_dongles(t_coder *coder, t_manager *mng)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	coder->left_dongle->is_used = false;
	coder->left_dongle->cooldown_end = get_rel_time(
			mng) + mng->arg->dongle_cooldown;
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	coder->right_dongle->is_used = false;
	coder->right_dongle->cooldown_end = get_rel_time(
			mng) + mng->arg->dongle_cooldown;
	pthread_mutex_unlock(&coder->right_dongle->mutex);
}

void	*routine(void *arg)
{
	t_routine_arg	*args;

	args = (t_routine_arg *) arg;
	// if (args->coder->id % 2 == 0)
	// {
	// 	heap_push(args->coder->left_dongle, args->coder, args->manager);
	// 	heap_push(args->coder->right_dongle, args->coder, args->manager);
	// }
	// else
	// {
	// 	psleep(500);
	// 	heap_push(args->coder->left_dongle, args->coder, args->manager);
	// 	heap_push(args->coder->right_dongle, args->coder, args->manager);
	// }
	while (args->coder->nb_compiles < args->manager->arg->nb_compiles
		&& !is_ended(args->manager))
	{
		if (args->manager->arg->nb_coders == 1)
			return (NULL);
		pickup_dongles(args->coder, args->manager);
		compile(args->coder, args->manager);
		release_dongles(args->coder, args->manager);
		refactor(args->coder, args->manager);
		debug(args->coder, args->manager);
		heap_push(args->coder->left_dongle, args->coder, args->manager);
		heap_push(args->coder->right_dongle, args->coder, args->manager);
	}
	return (NULL);
}

void	start_simulation(t_manager *mng)
{
	int	i;

	i = -1;
	mng->coders_threads = malloc(sizeof(pthread_t) * mng->arg->nb_coders);
	mng->routine_args = malloc(sizeof(t_routine_arg) * mng->arg->nb_coders);
	while (++i < mng->arg->nb_coders)
	{
		mng->routine_args[i].manager = mng;
		mng->routine_args[i].coder = &mng->coders[i];
		if (pthread_create(&mng->coders_threads[i],
			NULL, &routine, &mng->routine_args[i]) != 0)
			return ;
	}
}
