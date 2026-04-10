/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:47:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/10 18:34:30 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*routine(void *args)
{
	t_routine_arg	*arg;

	arg = (t_routine_arg *)args;
	while (arg->coder->time_to_burnout > get_rel_time(arg->manager)
		&& arg->coder->nb_compiles < arg->manager->args->nb_compiles)
	{
		printf("waiting...\n");
		wait_for_dongles(arg->coder, arg->manager);
		printf("compiling...\n");
		compile(arg->coder, arg->manager);
		printf("debugging...\n");
		debug(arg->coder, arg->manager);
		printf("refactoring...\n");
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
		i++;
	}
	i = -1;
	while (++i < mng->args->nb_coders)
		pthread_join(threads[i], NULL);
	free(threads);
	free(args);
	return (0);
}
