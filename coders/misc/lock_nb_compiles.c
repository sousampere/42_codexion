/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_nb_compiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 11:38:23 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/21 11:38:26 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

int	get_nb_compiles(t_coder *coder, t_manager *mng)
{
	int	nb_compiles;

	pthread_mutex_lock(&mng->gobal_mtx);
	nb_compiles = coder->nb_compiles;
	pthread_mutex_unlock(&mng->gobal_mtx);
	return (nb_compiles);
}

int	has_enough_compiles(t_coder *coder, t_manager *mng)
{
	int	nb_compiles;
	int	needed_compiles;

	nb_compiles = get_nb_compiles(coder, mng);
	pthread_mutex_lock(&mng->gobal_mtx);
	needed_compiles = mng->arg->nb_compiles;
	pthread_mutex_unlock(&mng->gobal_mtx);
	return (nb_compiles >= needed_compiles);
}
