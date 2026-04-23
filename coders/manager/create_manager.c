/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:31:18 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/23 16:55:43 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	push_coders(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
		init_heap(mng->coders[i].left_dongle);
	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (mng->coders[i].id % 2 != 0)
		{
			heap_push(mng->coders[i].left_dongle, &mng->coders[i], mng);
			heap_push(mng->coders[i].right_dongle, &mng->coders[i], mng);
		}
	}
	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (mng->coders[i].id % 2 == 0)
		{
			heap_push(mng->coders[i].left_dongle, &mng->coders[i], mng);
			heap_push(mng->coders[i].right_dongle, &mng->coders[i], mng);
		}
	}
	(void) mng;
	return ;
}

t_coder	*init_coders(t_manager *mng)
{
	t_coder	*coders;
	int		i;

	coders = malloc(sizeof(t_coder) * mng->arg->nb_coders);
	if (!coders)
		return (NULL);
	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		coders[i].id = i + 1;
		coders[i].burnout_delay = mng->arg->burnout_time;
		coders[i].nb_compiles = 0;
		coders[i].dongles_status = 0;
	}
	return (coders);
}

void	init_dongles(t_manager *mng)
{
	int			i;

	mng->dongles = ft_calloc(mng->arg->nb_coders, sizeof(t_dongle));
	if (!mng->dongles)
		return ;
	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		mng->coders[i % mng->arg->nb_coders].left_dongle = \
&mng->dongles[i % mng->arg->nb_coders];
		mng->coders[i % mng->arg->nb_coders].right_dongle = \
&mng->dongles[(i + 1) % mng->arg->nb_coders];
		mng->coders[i % mng->arg->nb_coders].left_dongle->id = i + 1;
		mng->coders[i % mng->arg->nb_coders].left_dongle->is_used = false;
		mng->coders[i % mng->arg->nb_coders].left_dongle->cooldown_end = 0;
		pthread_mutex_init(&mng->coders[i].left_dongle->mutex, NULL);
	}
	push_coders(mng);
}

t_manager	*init_manager(int argc, char **argv)
{
	t_manager	*mng;

	if (argc != 9)
		return (NULL);
	mng = malloc(sizeof(t_manager));
	if (!mng)
		return (NULL);
	mng->arg = get_args(argc, argv);
	if (!mng->arg)
	{
		free(mng);		
		return (NULL);
	}
	mng->coders = init_coders(mng);
	if (!mng->coders)
		return (NULL);
	init_dongles(mng);
	mng->start_timestamp = get_time_in_ms();
	mng->is_ended = false;
	pthread_mutex_init(&mng->printf_mtx, NULL);
	pthread_mutex_init(&mng->gobal_mtx, NULL);
	pthread_mutex_init(&mng->rel_time_mtx, NULL);
	return (mng);
}
