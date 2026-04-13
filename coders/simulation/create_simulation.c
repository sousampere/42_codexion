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

void	print(t_coder *coder, t_manager *mng, int code)
{
	// printf("Locking printf\n");
	pthread_mutex_lock(&mng->print_mutex);
	// printf("Printf locked\n");
	if (code == 1)
	{
		printf("\033[0;33m%ld %d has taken a dongle.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
		printf("\033[0;33m%ld %d has taken a dongle.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	}
	if (code == 2)
		printf("\033[0;36m%ld %d is compiling.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	if (code == 3)
		printf("\033[0;34m%ld %d is refactoring.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	if (code == 4)
		printf("\033[0;35m%ld %d is debugging.\033[0m\n",
			get_rel_time(mng), coder->coder_id);
	// printf("Unlcking printf\n");
	pthread_mutex_unlock(&mng->print_mutex);
	// printf("Printf unlocked\n");
}

void	*routine(void *arguments)
{
	t_routine_arg	*args;

	args = (t_routine_arg*) arguments;
	pthread_mutex_lock(&args->mng->start_mutex);

	// Wait for thead being operationnal
	heap_push(args->coder->left_dongle, args->coder, args->mng);
	while (!args->mng->start_flag)
		pthread_cond_wait(&args->mng->wait_condition, &args->mng->start_mutex);
	pthread_mutex_unlock(&args->mng->start_mutex);

	// while (args->coder->time_to_burnout > get_rel_time(args->mng) && args->coder->nb_compiles < args->mng->args->nb_compiles)
	// {

	// }
	printf("%d finished its work\n", args->coder->coder_id);
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
		args[i].mng = mng;
		printf("%d -> %d\n", mng->coders[i].coder_id, mng->coders[i].left_dongle->heap[0]->coder_id);
		pthread_create(&threads[i], NULL, &routine, &args[i]);
	}
	
	// sleep(1);
	pthread_mutex_lock(&mng->start_mutex);
	mng->start_flag = 1;
	pthread_mutex_unlock(&mng->start_mutex);
	// sleep(1);
	pthread_cond_broadcast(&mng->wait_condition);
	i = -1;
	while (++i < mng->args->nb_coders)
		pthread_join(threads[i], NULL);
	sleep(1);
}
