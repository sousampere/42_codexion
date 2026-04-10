/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:49:31 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/10 16:45:14 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	print(t_coder *coder, t_manager *mng, int code)
{
	// printf("Locking printf\n");
	pthread_mutex_lock(&mng->print_mutex);
	// printf("Printf locked\n");
	if (code == 1)
	{
		printf("\033[0;33m%ld %d has taken a dongle.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
		printf("\033[0;33m%ld %d has taken a dongle.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	}
	if (code == 2)
		printf("\033[0;36m%ld %d is compiling.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	if (code == 3)
		printf("\033[0;34m%ld %d is refactoring.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	if (code == 4)
		printf("\033[0;35m%ld %d is debugging.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	// printf("Unlcking printf\n");
	pthread_mutex_unlock(&mng->print_mutex);
	// printf("Printf unlocked\n");
}
