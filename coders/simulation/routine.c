/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaspard <gaspard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:52:38 by gaspard           #+#    #+#             */
/*   Updated: 2026/04/08 10:37:40 by gaspard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

void	*routine(void *coder)
{
	t_coder	*current_coder;

	current_coder = (t_coder *) coder;
	pick_dongle(coder);
	printf("coder %d coding with %d...\n", current_coder->coder_id, current_coder->left_dongle->dongle_id);
	printf("coder %d coding with %d...\n", current_coder->coder_id, current_coder->right_dongle->dongle_id);
	printf("====\n");
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
		// start thread
		pthread_create(&threads[i], NULL, &routine, &mng->coders[i]);
		// pthread_join(threads[i], NULL);
		i++;
	}
	sleep(5);
	return (0);
}
