/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:52:22 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/07 16:58:21 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

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
