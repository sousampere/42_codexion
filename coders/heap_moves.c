/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:26:24 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/09 14:00:58 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*heap_pop(t_dongle	*dongle)
{
	t_coder	*temp;

	if (dongle->heap[0] == NULL)
		return (NULL);
	temp = dongle->heap[0];
	dongle->heap[0] = dongle->heap[1];
	dongle->heap[1] = NULL;
	return (temp);
}

void	heap_push(t_dongle *dongle, t_coder *coder, t_manager *mng)
{
	if (!dongle->heap[0] && !dongle->heap[1])
		dongle->heap[0] = coder;
	if (dongle->heap[0] != NULL && !dongle->heap[1])
	{
		if (strcmp(mng->args->scheduler, "fifo") == 0)
			dongle->heap[1] = coder;
		else if (strcmp(mng->args->scheduler, "edf") == 0)
		{
			if (dongle->heap[0]->time_to_burnout < coder->time_to_burnout)
				dongle->heap[1] = coder;
			else
			{
				dongle->heap[1] = dongle->heap[0];
				dongle->heap[0] = coder;
			}
		}
	}
}

void	heap_rm(t_coder *coder)
{
	if (coder->left_dongle->heap[0]->coder_id == coder->coder_id)
		heap_pop(coder->left_dongle);
	if (coder->right_dongle->heap[0]->coder_id == coder->coder_id)
		heap_pop(coder->right_dongle);
}
