/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtourdia <@student.42mulhouse.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:52:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/07 16:52:10 by gtourdia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*routine(void *coder)
{
	t_coder	*current_coder;

	current_coder = (t_coder *) coder;
	printf("coder %d coding...\n", current_coder->coder_id);
	printf("coder %d has left_dongle of time %ld...\n", current_coder->coder_id, current_coder->left_dongle->cooldown);
	printf("coder %d has right_dongle of time %ld...\n", current_coder->coder_id, current_coder->right_dongle->cooldown);
	return (NULL);
}

int	start_simulation(t_manager *mng)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(pthread_t) * mng->args->nb_coders);
	i = 0;
	while (i < mng->args->nb_coders)
	{
		pthread_create(&threads[i], NULL, &routine, &mng->coders[i]);
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}