/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 07:18:52 by gtourdia          #+#    #+#             */
/*   Updated: 2026/04/04 09:03:56 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// Overflow, negative, non-integer and non-digit protection
int	is_invalid_value(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
	{
		if (string[i] < '0' || string[i] > '9')
			return (1);
	}
	if (strlen(string) > 10)
		return (1);
	if (strlen(string) >= 9 && string[9] >= '8')
	{
		string[9] = '\0';
		if (atoi(string) >= 214748364)
			return (1);
	}
	return (0);
}

int	validate_args(char **argv)
{
	int	i;

	i = 0;
	while (++i)
	{
		if (i == 8)
			break ;
		if (is_invalid_value(argv[i]))
			return (0);
	}
	return (1);
}

t_args	*get_args(int argc, char **argv)
{
	t_args	*args_ptr;

	args_ptr = malloc(sizeof(t_args));
	if (!args_ptr)
		return (NULL);
	if (argc != 9)
		return (NULL);
	if (!validate_args(argv))
		return (NULL);
	args_ptr->nb_coders = atoi(argv[1]);
	args_ptr->burnout_time = atoi(argv[2]);
	args_ptr->compile_time = atoi(argv[3]);
	args_ptr->debug_time = atoi(argv[4]);
	args_ptr->refactor_time = atoi(argv[5]);
	args_ptr->nb_compiles = atoi(argv[6]);
	args_ptr->dongle_cooldown = atoi(argv[7]);
	args_ptr->scheduler = argv[8];
	if (!(strcmp(argv[8], "fifo") == 0) && !(strcmp(argv[8], "edf") == 0))
		return (NULL);
	args_ptr->scheduler = argv[8];
	printf("%s\n\n", args_ptr->scheduler);
	return (args_ptr);
}
