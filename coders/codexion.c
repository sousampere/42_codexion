/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:22 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/18 17:41:53 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_manager	*mng;

	mng = init_manager(argc, argv);
	if (!mng)
		return (printf("Invalid argument.\n"), 1);
	start_simulation(mng);
	start_monitor(mng);
	// int i = -1;
	// while (i < mng->arg->nb_coders)
	// {
	// 	printf("---coder_%d---\n-> left heap 0 = %d, left_heap 1 = %d",
	// 	mng->coders[i].id, mng->coders[i].left_dongle->heap[0]->id, mng->coders[i].left_dongle->heap[0]->id);
	// }
	free_all(mng);
}
