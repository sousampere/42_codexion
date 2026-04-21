/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_burnout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:38:14 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/21 11:38:16 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	get_burnout(t_manager *mng, t_coder *coder)
{
	int	delay;

	pthread_mutex_lock(&mng->gobal_mtx);
	delay = coder->burnout_delay;
	pthread_mutex_unlock(&mng->gobal_mtx);
	return (delay);
}
