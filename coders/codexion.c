/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 05:42:19 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/04 09:00:49 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_args	*args;

	args = get_args(argc, argv);
	if (!args)
		return (printf("Invalid arguments.\n"), 1);
	printf("%s\n", args->scheduler);
	debug_args(args);
	free(args);
}
