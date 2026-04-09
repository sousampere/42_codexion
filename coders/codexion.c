/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 05:42:19 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/09 14:19:34 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_manager	*manager;

	manager = create_manager(argc, argv); // Get manager
	start_simulation(manager);
	monitor_burnout(manager); // Starts monitoring burn-out or simulation end
	free_all(manager);
	return (0);
}
