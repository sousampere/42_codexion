/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:04:33 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/21 12:04:35 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

bool	is_ended(t_manager *mng)
{
	bool	status;

	pthread_mutex_lock(&mng->gobal_mtx);
	status = mng->is_ended;
	pthread_mutex_unlock(&mng->gobal_mtx);
	return (status);
}
