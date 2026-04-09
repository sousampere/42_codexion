/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:47:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/09 14:23:00 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*routine(void *args)
{
	t_routine_arg	*arg;

	arg = (t_routine_arg*)args;
	// printf("%d < %ld\n", arg->coder->time_to_burnout, get_rel_time(arg->manager));
	while (arg->coder->time_to_burnout > get_rel_time(arg->manager)
	&& arg->coder->nb_compiles < arg->manager->args->nb_compiles)
	{
		take_dongles(arg->coder, arg->manager);
		compile(arg->coder, arg->manager);
		refactor(arg->coder, arg->manager);
	}
	return (NULL);
}


int	start_simulation(t_manager *mng)
{
	pthread_t		*threads;
	t_routine_arg	*args;
	int				i;

	threads = malloc(sizeof(pthread_t) * mng->args->nb_coders);
	args = malloc(sizeof(t_routine_arg) * mng->args->nb_coders);
	i = 0;
	while (i < mng->args->nb_coders)
	{
		args[i].coder = &mng->coders[i];
		args[i].manager = mng;
		pthread_create(&threads[i], NULL, &routine, &args[i]);
		// pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}

