/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 05:42:19 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/12 15:04:48 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_manager	*mng;
	(void) argc;
	(void) argv;
	mng = create_manager(argc, argv);
	create_simulation(mng);
	// create simulation
	// start simulation
	// start monitoring
	// printf("dongles===\n%d\n", mng->dongles[mng->args->nb_coders - 1].dongle_id);
	// printf("%ld\n", mng->dongles[mng->args->nb_coders - 1].cooldown);
	// printf("%d\n", mng->dongles[mng->args->nb_coders - 1].is_in_use);
	// printf("%d\n", mng->coders[mng->args->nb_coders - 1].coder_id);
	// printf("%d\n", mng->coders[0].left_dongle->dongle_id);
	return (0);
}
