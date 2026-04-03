/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 05:42:19 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/03 14:18:09 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_args	*args;

	args = get_args(argc, argv);
	if (!args)
		return (printf("Invalid arguments.\n"), 1);
	printf("%d", args->dongle_cooldown);
}
