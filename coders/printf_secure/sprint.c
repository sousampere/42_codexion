/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:44 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 18:39:21 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	sprint(t_coder *coder, t_manager *mng, int code)
{
	pthread_mutex_lock(&mng->printf_mtx);
	if (code == 1 && !mng->is_ended)
	{
		printf("\033[0;33m%d %d has taken a dongle\033[0m\n",
			get_rel_time(mng), coder->id);
		printf("\033[0;33m%d %d has taken a dongle\033[0m\n",
			get_rel_time(mng), coder->id);
	}
	if (code == 2 && !mng->is_ended)
		printf("\033[0;36m%d %d is compiling\033[0m\n",
			get_rel_time(mng), coder->id);
	if (code == 3 && !mng->is_ended)
		printf("\033[0;34m%d %d is refactoring\033[0m\n",
			get_rel_time(mng), coder->id);
	if (code == 4 && !mng->is_ended)
		printf("\033[0;35m%d %d is debugging\033[0m\n",
			get_rel_time(mng), coder->id);
	if (code == 5)
		printf("\033[0;31m%d %d burned out\033[0m\n",
			get_rel_time(mng), coder->id);
	if (code == 6)
		printf("🏁 === Simulation ended. Exiting the matrix ===\n");
	pthread_mutex_unlock(&mng->printf_mtx);
}
