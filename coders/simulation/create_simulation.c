/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_simulation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 14:56:46 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/12 15:21:51 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*routine(void *arguments)
{
	t_routine_arg	*args;

	args = (t_routine_arg*) arguments;
	pthread_mutex_lock(&args->mng->start_mutex);
	while (!args->mng->start_flag)
		pthread_cond_wait(&args->mng->wait_condition, &args->mng->start_mutex);
	pthread_mutex_unlock(&args->mng->start_mutex);
	
	// code
	printf("hello %d\n", args->coder->coder_id);
	return (NULL);
}

void	create_simulation(t_manager *mng)
{
	// lance les threads un par un
	int				i;
	pthread_t		*threads;
	t_routine_arg	*args;

	i = -1;
	threads = malloc(sizeof(pthread_t) * mng->args->nb_coders);
	args = malloc(sizeof(t_routine_arg) * mng->args->nb_coders);
	pthread_cond_init(&mng->wait_condition, NULL);
	while (++i < mng->args->nb_coders)
	{
		args[i].coder = &mng->coders[i];
		printf("%d\n", args[i].coder->coder_id);
		args[i].mng = mng;
		pthread_create(&threads[i], NULL, &routine, &args[i]);
	}
	
	i = -1;
	sleep(1);
	pthread_mutex_lock(&mng->start_mutex);
	mng->start_flag = 1;
	pthread_mutex_unlock(&mng->start_mutex);
	sleep(1);
	pthread_cond_broadcast(&mng->wait_condition);
	sleep(1);
}
