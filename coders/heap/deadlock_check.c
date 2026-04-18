/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deadlock_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:40:06 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 17:40:17 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

bool	will_deadlock(t_manager *mng)
{
	int	i;

	i = -1;
	while (++i < mng->arg->nb_coders)
	{
		if (mng->coders[i].left_dongle->heap[0] == NULL)
			return (true);
		if (mng->coders[i].left_dongle->heap[0]->id == mng->coders[i].id)
			return (false);
	}
	return (true);
}
