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
		if (!has_enough_compiles(&mng->coders[i], mng))
			return (false);
	}
	pthread_mutex_lock(&mng->gobal_mtx);
	mng->is_ended = true;
	pthread_mutex_unlock(&mng->gobal_mtx);
	sprint(&mng->coders[0], mng, 6);
	return (true);
}

bool	check_burnout(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (get_rel_time(mng) >= get_burnout(mng, &mng->coders[i])
			&& has_enough_compiles(&mng->coders[i], mng))
		{
			pthread_mutex_lock(&mng->gobal_mtx);
			mng->is_ended = true;
			pthread_mutex_unlock(&mng->gobal_mtx);
			sprint(&mng->coders[i], mng, 5);
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
	{
		psleep(1000);
		continue ;
	}
	return (NULL);
}

void	start_monitor(t_manager *mng)
{
	pthread_t	thread;

	pthread_mutex_lock(&mng->gobal_mtx);
	mng->is_ended = 0;
	pthread_mutex_unlock(&mng->gobal_mtx);
	pthread_create(&thread, NULL, &monitor_routine, mng);
	pthread_join(thread, NULL);
}
