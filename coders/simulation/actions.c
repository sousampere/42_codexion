/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:47:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/08 10:39:08 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	pick_dongle(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	if (coder->left_dongle->is_in_use == 0)
	{
		printf("Using dongle.\n");
		sleep(1);
	}
	pthread_mutex_unlock(&coder->left_dongle->mutex);
}