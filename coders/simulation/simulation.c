/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:47:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/11 14:42:49 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*routine(void *args)
{
	t_routine_arg	*arg;

	arg = (t_routine_arg *)args;
	pthread_mutex_lock(&arg->manager->start_mutex);
	while (arg->manager->start == 0)
		pthread_cond_wait(&arg->manager->start_cond, &arg->manager->start_mutex);
	pthread_mutex_unlock(&arg->manager->start_mutex);
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
		printf("LAUNCHING THREAD %d\n", i);
		i++;
	}
	i = -1;
	// monitor_burnout(mng);
	pthread_mutex_lock(&mng->start_mutex);
	mng->start = 1;
	printf("broadcasting\n");
	pthread_cond_broadcast(&mng->start_cond);
	pthread_mutex_unlock(&mng->start_mutex);
	while (++i < mng->args->nb_coders)
		pthread_join(threads[i], NULL);
	free(threads);
	free(args);
	return (0);
}
