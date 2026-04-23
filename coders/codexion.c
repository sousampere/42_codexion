/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 17:26:22 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/23 16:57:54 by gtourdia         ###   ########.fr       */
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
	free_all(mng);
}
