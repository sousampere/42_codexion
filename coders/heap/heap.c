/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:38:56 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 18:41:51 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	init_heap(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mtx_heap);
	dongle->heap[0] = NULL;
	dongle->heap[1] = NULL;
	pthread_mutex_unlock(&dongle->mtx_heap);
}

bool	has_heap_priority(t_dongle *dongle, t_coder *coder)
{
	bool	status;

	pthread_mutex_lock(&dongle->mtx_heap);
	if (dongle->heap[0] == NULL)
		status = true;
	else
		status = dongle->heap[0]->id == coder->id;
	pthread_mutex_unlock(&dongle->mtx_heap);
	return (status);
}

void	heap_pop(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mtx_heap);
	dongle->heap[0] = dongle->heap[1];
	dongle->heap[1] = NULL;
	pthread_mutex_unlock(&dongle->mtx_heap);
}

void	heap_push(t_dongle *dongle, t_coder *coder, t_manager *mng)
{
	pthread_mutex_lock(&dongle->mtx_heap);
	if (dongle->heap[0] == NULL)
	{
		dongle->heap[0] = coder;
		pthread_mutex_unlock(&dongle->mtx_heap);
		return ;
	}
	if (mng->arg->scheduler == 1)
		dongle->heap[1] = coder;
	else
	{
		if (coder->burnout_delay <= dongle->heap[0]->burnout_delay)
		{
			dongle->heap[1] = dongle->heap[0];
			dongle->heap[0] = coder;
		}
		else
			dongle->heap[1] = coder;
	}
	pthread_mutex_unlock(&dongle->mtx_heap);
}

void	heap_rm(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mtx_heap);
	if (dongle->heap[0] == NULL)
	{
		pthread_mutex_unlock(&dongle->mtx_heap);
		return ;
	}
	else if (dongle->heap[0]->id == coder->id)
	{
		dongle->heap[0] = dongle->heap[1];
		dongle->heap[1] = NULL;
	}
	else if (dongle->heap[1] != NULL && dongle->heap[1]->id == coder->id)
		dongle->heap[1] = NULL;
	pthread_mutex_unlock(&dongle->mtx_heap);
}
