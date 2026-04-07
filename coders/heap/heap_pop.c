/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:26:24 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/07 17:11:20 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

t_coder	*heap_pop(t_dongle	*dongle)
{
	t_dongle	*temp;

	if (dongle->heap[0] == NULL)
		return (NULL);
	temp = dongle->heap[0];
	dongle->heap[0] = dongle->heap[1];
	dongle->heap[1] = NULL;
	return (temp);
}
