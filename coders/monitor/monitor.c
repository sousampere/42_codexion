/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:30:23 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 18:37:14 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

bool	check_end(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (mng->coders[i].nb_compiles != mng->arg->nb_compiles)
			return (false);
	}
	mng->is_ended = true;
	sprint(&mng->coders[0], mng, 6);
	return (true);
}

bool	check_burnout(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (get_rel_time(mng) >= mng->coders[i].burnout_delay && mng->coders[i].nb_compiles < mng->arg->nb_compiles)
		{
			mng->is_ended = true;
			sprint(&mng->coders[i], mng, 5);
			printf("coder_%d, left_used=%d, right_used=%d, left_priority=%d, left_cooldown=%d, right_cooldown=%d\n",
				mng->coders[i].id, mng->coders[i].left_dongle->is_used, mng->coders[i].right_dongle->is_used, has_heap_priority(mng->coders[i].left_dongle, &mng->coders[i]),
				mng->coders[i].left_dongle->cooldown_end <= get_rel_time(mng), mng->coders[i].right_dongle->cooldown_end <= get_rel_time(mng));
			return (true);
		}
	}
	return (false);
}

void	*monitor_routine(void *arg)
{
	t_manager	*mng;

	mng = (t_manager *) arg;
	while (!check_end(mng) && !check_burnout(mng))
		continue ;
	return (NULL);
}

void	start_monitor(t_manager *mng)
{
	pthread_t	thread;

	mng->is_ended = 0;
	pthread_create(&thread, NULL, &monitor_routine, mng);
	pthread_join(thread, NULL);
}
